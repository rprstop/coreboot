/* For starting coreboot in protected mode */

#include <arch/rom_segs.h>
#include <cpu/x86/post_code.h>

	.code32


	/* This is the GDT for the ROM stage part of coreboot. It
	 * is different from the RAM stage GDT which is defined in
	 * c_start.S
	 * GDT(Global Descriptor Tables)
	 */
	/*HTKIM
	 * IA-32 Vol.3A 5-2
	 * The processor's protection mechanism uses the following fields and flags
	 * int the system data structures to control access to segments and pages
	 * .Descriptor type (S) flag - (Bit 12) system segment or a code or data segment.
	 * .Type field - (Bit 8 through 11 in hte second doubleword of a segment descriptor)
	 * 				determines the type of code, data, or system seg.
	 * .Limit field - (Bits 0 through 15 of the first doubleword and bits 16 through 19
	 *				of the second doubleword of a segment descriptor) Determines the size of
	 *				the segment, along with the G flag and E flag (for data segments)
	 * .G flag - (Bit 23 in the second doubleword of a segment descriptor) Determines the
	 *			 size of the segment, along with limit field and E flag (for data segments)
	 * .E flag - (Bit 10 in the second doubleword of a data-segment descriptor) Determines the
	 *			 sieze of the segment, along with limit field and G flag.
	 * .Descriptor privilege level (DPL) field - (Bits 13 and 14 in the second doubleword of
	 *			 a segment descriptor) Determines the privilege level of the segment.
	 * .Requested privilege level(RPL) field - (Bits 0 and 1 of any segment selector)
	 * 			 Specifies the requested privilege level of a segment selector.
	 * .Current privilege level(CPL) field - (Bits 0 and 1 of the CS segment register)
	 *			 Indicates the privilege level of the currently executing program or procedure.
	 * .User/supervisor (U/S)flag - (Bit 2 of paging-structure entries) Determines the type of
	 * 			 page: user or supervisor.
	 * .Read/write (R/W) flag - (bit 1 of paging-structure entries) Determines the type of
	 * 			 access allowed to a page: read-only or read/write.
	 * .Execute-disable (XD) flag - (Bit 63 of certain paging-structure entries) Determines
	 * 			 the type of access allowed to a page: executable or not-executable.
	 */

	.align	4
.globl gdtptr
gdt:
gdtptr:
	.word	gdt_end - gdt -1 /* compute the table limit */
	.long	gdt		 /* we know the offset */
	.word	0

	/* HTKIM
	 * Data-segment Descriptor
	 * 31			24 23  22  21 20 19	 16 15 14 13 12 11	      8 7			0
	 * |- base31:24 -| G | B | 0 |AVL|Limit|p|- DPL-|1|Type 0 E W A|-Base 23:16 -|
	 *
	 * 31								 16 15 									0
	 * |-------Base Address 15:00 ---------|-------------Segment Limit 15:00-----|
	 *
	 * Code-Segment Descriptor
	 * 31			24 23  22  21 20 19	 16 15 14 13 12 11	      8 7			0
	 * |- base31:24 -| G | B | 0 |AVL|Limit|p|- DPL-|1|Type 0 C R A|-Base 23:16 -|
	 *
	 * 31								 16 15 									0
	 * |-------Base Address 15:00 ---------|-------------Segment Limit 15:00-----|
	 *
	 * System-Segment Descriptor
	 * 31			24 23  22  21 20 19	 16 15 14 13 12 11	      8 7			0
	 * |- base31:24 -| G |   | 0 |   |Limit|p|- DPL-|0|--- Type ---|-Base 23:16 -|
	 *
	 * 31								 16 15 									0
	 * |-------Base Address 15:00 ---------|-------------Segment Limit 15:00-----|
	 *
	 * A : Accessed,		AVL : Available to Sys. Programmer's,	B : Big
	 * G : Granularity		C : Conforming							R : Readable
	 * D : Default			LIMIT : Segment Limit					P : Present
	 *   : Reserved			DPL : Descriptor Privilege Level
	 *
	 * IA-32 5-3 Limit Checking
	 * When the G flag is clear (byte granularity), the effective limit is the value
	 * of the 20-bit limit field in the segment descriptor. Here, the limit ranges
	 * from 0 to FFFFFH(1 MByte). When the G flag is set(4-KByte page granularity),
	 * the processor scales the value in the limit field by a factor of 2^12(4 KBytes).
	 * In this case, the effective limit ranges from FFFH(4 KBytes) to FFFF_FFFFH( 4G).
	 * Note that when scaling is used (G flag is set), the lower 12 bits of a segment
	 * offset (address) are not checked aginst the limit;
	 */


	/* selgdt 0x08, flat(unsegment) code segment */
	.word	0xffff, 0x0000
	.byte	0x00, 0x9b, 0xcf, 0x00 /* G=1 and 0x0f, So we get 4Gbytes for limit */
	/* HTKIM
	 *
	 * Code-Segment Descriptor
	 * 0x0093cf00
	 * 31			24 23  22  21 20 19	 16 15 14 13 12 11	      8 7			0
	 * |- base31:24 -| G | B | 0 |AVL|Limit|p|- DPL-|1|Type 0 C R A|-Base 23:16 -|
	 *  0000_0000      1   0   0   1  1011  1   10   0      1 1 1 1   0000_0000
	 *
	 * 0xffff_0000
	 * 31								 16 15 									0
	 * |-------Base Address 15:00 ---------|-------------Segment Limit 15:00-----|
	 */


	/* selgdt 0x10,flat data segment */
	.word	0xffff, 0x0000
	.byte	0x00, 0x93, 0xcf, 0x00
	/* HTKIM
	*
	 * Data-segment Descriptor
	 * 0x0093cf00
	 * 31			24 23  22  21 20 19	 16 15 14 13 12 11	      8 7			0
	 * |- base31:24 -| G | B | 0 |AVL|Limit|p|- DPL-|1|Type 0 E W A|-Base 23:16 -|
	 *  0000_0000      1   0   0   1  0011  1   10   0      1 1 1 1   0000_0000
	 *
	 * 0xffff_0000
	 * 31								 16 15 									0
	 * |-------Base Address 15:00 ---------|-------------Segment Limit 15:00-----|
	 */

gdt_end:


/*
 *	When we come here we are in protected mode. We expand
 *	the stack and copies the data segment from ROM to the
 *	memory.
 *
 *	After that, we call the chipset bootstrap routine that
 *	does what is left of the chipset initialization.
 *
 *	NOTE aligned to 4 so that we are sure that the prefetch
 *	cache will be reloadeg.
 */
	.align	4
.globl protected_start
protected_start:

	lgdt	%cs:gdtptr /* CS : code-segment */
	ljmp	$ROM_CODE_SEG, $__protected_start

__protected_start:
	/* Save the BIST value */
	movl	%eax, %ebp
	/* 스택의 시작 지점 주소를 eax 레지스터에 저장 */

	post_code(POST_ENTER_PROTECTED_MODE)

	/* HTKIM
	 * Segment Register
	 * CS : Code segment
	 * DS : Data seg
	 * SS : Stack seg
	 * ES/FS/GS : Extra seg pointer
	 */
	/* HTKIM
	 * EAX : Accumulator for operands and results data
	 * EBX : Pointer to data in the data memory segment
	 *						  EAX
	 * |------------------------------------------------|
	 * 31					  15     AH    7      AL    0
	 * |-----------------------|-----------|------------|
	 *                         |----------AX------------|
	 *
	 *						  EBX
	 * |------------------------------------------------|
	 * 31					  15     BH    7      BL    0
	 * |-----------------------|-----------|------------|
	 *                         |----------BX------------|
	 */

	movw	$ROM_DATA_SEG, %ax
	movw	%ax, %ds
	movw	%ax, %es
	movw	%ax, %ss
	movw	%ax, %fs
	movw	%ax, %gs
	/* HTKIM
	 * ToDo:각각의 segment reg들이 ax로 movw 되면서 어떻게 되나?
	 */

	/* Restore the BIST value to %eax */
	movl	%ebp, %eax

