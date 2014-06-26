/*
 *      _ROMTOP                 : The top of the rom used where we
 *				  need to put the reset vector.
 */

SECTIONS {
	/* Trigger an error if I have an unuseable start address */
	_bogus = ASSERT(_start >= 0xffff0000, "_start too low. Please report.");
	/* reset16 segment는 0xfffffff0번지에 컴파일 되며, 0xffff0000번지 내에 _start
	 * 가 존재 하여야 한다.(ffff -> 64kb)
	 */
	_ROMTOP = 0xfffffff0;
	. = _ROMTOP;
	.reset . : {
		*(.reset)
		. = 15 ;
		BYTE(0x00);
	}
}
