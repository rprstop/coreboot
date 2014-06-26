	.section ".reset"
	.code16
.globl	reset_vector
reset_vector:
	.byte  0xe9
	.int   _start - ( . + 2 )
	/* segment는 0xe9(미리 정의된 opcde)로 점프한다.
	 * _start - ( . + 2 )를 _start-write로 보면된다.
	 * 다만 보통의 asm과 편차가 있는데, +2 해줘서
	 * 현재 실행되고 있는 instruction의 End point를 가르키도록?
	 */
	/* Note: The above jump is hand coded to work around bugs in binutils.
	 * 5 byte are used for a 3 byte instruction.  This works because x86
	 * is little endian and allows us to use supported 32bit relocations
	 * instead of the weird 16 bit relocations that binutils does not
	 * handle consistenly between versions because they are used so rarely.
	 */
	. = 0x8;
	.code32
	jmp	protected_start
	.previous
