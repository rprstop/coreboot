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

__fpu_start:
	/* Preserve BIST. eax : 0^4, ebp : 0000_0000H */
	movl	%eax, %ebp /* ebp : the frame pointer */
	/* HTKIM
	 * If BIST(Built-In Self-Test) is invoked on power up or reset, EAX is 0
	 * only if all tests passed.
	 */

	/*
	 * Clear the CR0[2] bit (the "Emulation" flag, EM).
	 *
	 * This indicates that the processor has an (internal or external)
	 * x87 FPU, i.e. floating point operations will be executed by the
	 * hardware (and not emulated in software).
	 *
	 * Additionally, if this bit is not cleared, MMX/SSE instructions won't
	 * work, i.e., they will trigger an invalid opcode exception (#UD).
	 */

	movl	%cr0, %eax /* cr0는 control reg */
	andl	$~(1 << 2), %eax /* cr0[2] bit을 clear하게 되는데, 이는 FPU를 */
							 /* software 말고 hardware로 사용 함 */
	movl	%eax, %cr0

	/* Restore BIST. */
	movl	%ebp, %eax
