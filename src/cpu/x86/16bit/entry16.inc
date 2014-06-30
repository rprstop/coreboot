/*
 * This software and ancillary information (herein called SOFTWARE)
 * called LinuxBIOS is made available under the terms described here.
 *
 * The SOFTWARE has been approved for release with associated
 * LA-CC Number 00-34. Unless otherwise indicated, this SOFTWARE has
 * been authored by an employee or employees of the University of
 * California, operator of the Los Alamos National Laboratory under
 * Contract No. W-7405-ENG-36 with the U.S. Department of Energy.
 *
 * The U.S. Government has rights to use, reproduce, and distribute this
 * SOFTWARE. The public may copy, distribute, prepare derivative works
 * and publicly display this SOFTWARE without charge, provided that this
 * Notice and any statement of authorship are reproduced on all copies.
 *
 * Neither the Government nor the University makes any warranty, express
 * or implied, or assumes any liability or responsibility for the use of
 * this SOFTWARE.  If SOFTWARE is modified to produce derivative works,
 * such modified SOFTWARE should be clearly marked, so as not to confuse
 * it with the version available from LANL.
 *
 * Copyright (C) 2000, Ron Minnich rminnich@lanl.gov
 *                     Advanced Computing Lab, LANL
 */


/* Start code to put an i386 or later processor into 32-bit protected mode.
 */

#include <arch/rom_segs.h>
.code16
.globl _start
.type _start, @function

_start:
	cli
	/* Save the BIST result */
	movl	%eax, %ebp
	/* HTKIM
	 * epb-스택의 시작 지점 주소
	 * eax-산술/논리연산에 사용되는 레지스터
	 * 스택의 시작 지점 주소를 eax 레지스터에 저장
	 */

	post_code(POST_RESET_VECTOR_CORRECT)

	/* IMMEDIATELY invalidate the translation lookaside buffer (TLB) before
	 * executing any further code. Even though paging is disabled we
	 * could still get false address translations due to the TLB if we
	 * didn't invalidate it. Thanks to kmliu@sis.com.tw for this TLB fix.
	 */

	xorl	%eax, %eax
  /* HTKIM
   * 자신의 값으로  xorl을 수행함으로 %eax의 값은 0
   */
	movl	%eax, %cr3    /* Invalidate TLB*/
  /* HTKIM
   * cr3레지스터는 x86 아키텍쳐에서 커널의 page_dir 물리 주소가 저장
   * 되어 있음.
   */


	/* Invalidating the cache here seems to be a bad idea on
	 * modern processors.  Don't.
	 * If we are hyperthreaded or we have multiple cores it is bad,
	 * for SMP startup.  On Opterons it causes a 5 second delay.
	 * Invalidating the cache was pure paranoia in any event.
	 * If you cpu needs it you can write a cpu dependent version of
	 * entry16.inc.
	 */

	/* Note: gas handles memory addresses in 16 bit code very poorly.
	 * In particular it doesn't appear to have a directive allowing you
	 * associate a section or even an absolute offset with a segment register.
	 *
	 * This means that anything except cs:ip relative offsets are
	 * a real pain in 16 bit mode.  And explains why it is almost
	 * impossible to get gas to do lgdt correctly.
	 *
	 * One way to work around this is to have the linker do the
	 * math instead of the assembler.  This solves the very
	 * pratical problem of being able to write code that can
	 * be relocated.
	 *
	 * An lgdt call before we have memory enabled cannot be
	 * position independent, as we cannot execute a call
	 * instruction to get our current instruction pointer.
	 * So while this code is relocateable it isn't arbitrarily
	 * relocatable.
	 *
	 * The criteria for relocation have been relaxed to their
	 * utmost, so that we can use the same code for both
	 * our initial entry point and startup of the second cpu.
	 * The code assumes when executing at _start that:
   * HTKIM
   * 메모리 주소의 기준을 정하는데 사용한 네 개의 세그먼트
   * 레지스터(CS, DS SS, ES)
   * CS : Code Segment / DS : Data Segment
   * SS : Stack Segment / ES : Extra Segment
   *
   * 현재 세그먼트에서 다음에 실행될 명령어의 offset을 저장하는 IP 레지스터
   *
	 * (((cs & 0xfff) == 0) and (ip == _start & 0xffff))
	 * or
	 * ((cs == anything) and (ip == 0)).
	 *
	 * The restrictions in reset16.inc mean that _start initially
	 * must be loaded at or above 0xffff0000 or below 0x100000.
	 *
	 * The linker scripts computes gdtptr16_offset by simply returning
	 * the low 16 bits.  This means that the intial segment used
	 * when start is called must be 64K aligned.  This should not
	 * restrict the address as the ip address can be anything.
	 *
	 * Also load an IDT with NULL limit to prevent the 16bit IDT being used
	 * in protected mode before c_start.S sets up a 32bit IDT when entering
	 * ram stage. In practise: CPU will shutdown on any exception.
	 * See IA32 manual Vol 3A 19.26 Interrupts.
	 */

	  /* HTKIM
	   * x86 general register (AX, BX, CX, DX)가 있으며, 그 크기는 16bit이다.
	   * general reg의 상위(AH), 하위(AL) 각각 8bit로 나뉜다.(독립적으로 1byte
	   * reg로 사용이 가능)
	   * AX - 누산기의 기능을 한다.
	   * BX - base reg이다. 간접적인 주소 방식을 위해 사용하는  reg.
	   * CX - count reg이다. loop, shift, rotate, string 명령에 사용.
	   * DX - data reg이다. word크기의 mul, div 연산을 할 때 AX와 함께 사용.
	   */

	movw	%cs, %ax	/* save new location */
	shlw	$4, %ax		/* shift word 4 times, multiply that vale by 2^4 */
	movw	$nullidt_offset, %bx /* nullidt_offset = .globl nullidt & oxffff */
	subw	%ax, %bx 	/* ax -bx */
	lidt	%cs:(%bx) 	/* Loads a value from an operand into the IDT regiter. */
						/* LIDT (Load Interrupt Descriptor Table Register)
						 * - Loads the IDT base address and limit from memory into memory.
						 */
	movw	$gdtptr16_offset, %bx /* gdtprt16_offset = .globl gdtptr16 & 0xffff */
	subw	%ax, %bx	/* ax -bx */
	data32  lgdt %cs:(%bx) /* LGDT(Load GDT Register)
							* - Loads the GDT base address and limit from memory
							* into the GDTR register.
							*/
						   /* data32 - Operand/Address size prefixes : data16, addr16,
						    * data32 and addr32
							*/

	movl	%cr0, %eax 	/* cr0 is control register. */
	andl	$0x7FFAFFD1, %eax /* PG,AM,WP,NE,TS,EM,MP = 0 */
	/* HEKIM
	 * PG - paging (bit 31 of CR0)
	 * CD - Cache Disable (bit 30 of CR0)
	 * NW - Not Write-through (bit 29 of CR0)
	 * AM - Alignment Mask (bit 18 of CR0)
	 * WP - write protect (bit 16 of CR0)
	 * NE - Numeric Error (bit 5 of CR0)
	 * ET - Extension Type (bit 4 of CR0)
	 * TS - Task Switched (bit 3 of CR0)
	 * EM - Emulation (bit 2 of CR0)
	 * MP - Monitor Coprocessor (bit 1 of CR0)
	 * PE - Protection Enable (bit 0 of CR0)
	 * PCD - Page-level Cache Disable (bit 4 of CR3)
	 * others - IA32 Vol.3A 2-22
	 *
	 */


	orl	$0x60000001, %eax /* CD, NW, PE = 1 */
	movl	%eax, %cr0

	/* Restore BIST(Built-In Self-Test) to %eax */
	movl	%ebp, %eax

	/* Now that we are in protected mode jump to a 32 bit code segment. */
	/* Long jump, use $ROM_CODE_SEG for the CS reg and __protected_start for
	 * the EIP reg.
	 * At&t - 'b', 'w', 'l' and 'q' at the end of the instruction.
	 * Calls : lcall/ljmp $section, $offset
	 */
	data32	ljmp	$ROM_CODE_SEG, $__protected_start

	/**
	 * The gdt is defined in entry32.inc, it has a 4 Gb code segment
	 * at 0x08, and a 4 GB data segment at 0x10;
	 */
.align	4
.globl gdtptr16
gdtptr16:
	.word	gdt_end - gdt -1 /* compute the table limit */
	.long	gdt		 /* we know the offset */

.align	4
.globl nullidt
nullidt:
	.word	0	/* limit */
	.long	0
	.word	0

.globl _estart
_estart:
	.code32

