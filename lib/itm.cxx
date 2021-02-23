#include "itm.h"
/**
 * Send character over ITM.
 * @param ch	Character to send.
 */
void ITM_putc(uint8_t ch) {

	//Enable TRCENA
	DBG_DEMCR |= DBG_DEMCR_TRCENA;

	//enable stimulus port 0
	ITM_TRACE_EN |= ITM_TRACE_EN_PORT0;

	// read FIFO status in bit [0]:
	while(!(ITM_STIMULUS_PORT0 & 1));

	//Write to ITM stimulus port0
	ITM_STIMULUS_PORT0 = ch;
}


/**
 * Send a string over ITEM.
 * @param s	String to send.
 */
void ITM_puts(const char *s) {
	while(*s)
		ITM_putc(*s++);
}

