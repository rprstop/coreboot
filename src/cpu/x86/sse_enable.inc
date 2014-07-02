/*
 * This file is part of the coreboot project.
 *
 * Copyright (C) 2002 Eric Biederman <ebiederm@xmission.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 2 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

	/* Preserve BIST. */
	movl	%eax, %ebp

	/* Enable SSE instructions. */
	/* HTKIM
	 * IA-32 Vol.3A 2-17
	 * 2.5 CR(control reg)
	 * - contain a variety of flags and data fields for
	 * controlling system-level operations.
	 * - determine operating mode of the processor and the characteristics
	 * of the currently executing task.
	 * |------------| CR4-contains a group of flags that enable several architectural extensions,
	 *					 and indicate operating system or executive support for specific processor
	 *					 capabilities.
	 * |------------| CR3-contains the physical addr of the base of the paging srtuctre.
	 * |------------| CR2-contains the page-fault linear address
	 * |------------| CR1-reserved
	 * |------------| CR0-control operating mode and state system control flags
	 */

	movl	%cr4, %eax
	orl	$(1 << 9), %eax
	/* HTKIM
	 * bit 9 of CR4 is that OSFXSR(Operating System Support for FXSAVE and FXRSTOR instructions.
	 * 이 비트가 1이면, FXSAVE and FXRSTOR instrucions을 지원한다. FXSAVE&FXRSTOR가 enable 되어
	 * 있으면, XMM & MXCSR & x87 FPU & MMX reg contents를 save하거나 restore한다.
	 * PAUSE, PREFETCHh, SFENCE, LFENCE, MFENCE, MOVNTI, CLFLUSH, CRC32 and POPCNT 예외사항 이외에
	 * SSE/SSE2,3,4를 실행한다.
	 * 반대로 이 비트가 0 이면, FXSAVE & FXRSTOR instructions은 x87 FPU & MMX instructions contents를
	 * save & restore 한다. 하지만 XMM & MXCSR reg는 save & resotre하지 않는다.
	 * PAUSE, PREFETCHh 등등 예외사항 이외에 SSE/SSE2/SSE3을 실행 하려 하면 invalid opcode excepton(#US)
	 * 가 발생하게 된다.
	 */
	movl	%eax, %cr4

	/* Restore BIST. */
	movl	%ebp, %eax

