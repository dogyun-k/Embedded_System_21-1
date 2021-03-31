ENTRY(Reset_Handler)

_estack = 0x20020000; /* end of RAM, 램에서 가장 큰 주소 */

MEMORY
{
	RAM (xrw)	: ORIGIN = 0x20000000, LENGTH = 128k /* SRAM 영역 메모리 주소 20000000부터 128k */
	ROM (rx)	: ORIGIN = 0x08000000,  LENGTH = 512k	 /* code 영역 내의 flash 주소 8000000부터 512k */
}

SECTIONS
{
	.isr_vector	: 
	{
		. = ALIGN(4);
		KEEP(*(.isr_vector))
		. = ALIGN(4);
	} >ROM

	.text :
	{
		. = ALIGN(4);	
		*(.text)
		. = ALIGN(4);	
	} >ROM

}

						
