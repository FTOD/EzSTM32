#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <itm.h>
#include "IO_F4_Discovery.h"


int main() {
    int i;

    // set power
	// ZHEN : USE rcc_periph_clock_enable(RCC_GPIOD), checkout rcc_common_all
	// ZHEN : it is nothing to do with the power anyway
    //RCC_AHB1ENR |= 1 << ID_GPIOD;
	
	// RCC clock setup
	rcc_clock_setup_pll(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);
	/* Enable GPIOD clock. */
	rcc_periph_clock_enable(RCC_GPIOD);



    // initialize the LEDs
	// ZHEN : USE gpio_mode_setup 
    //GPIO_MODER_SET(LED_ORANGE, GPIO_MODER_OUT);
    //GPIO_MODER_SET(LED_BLUE, GPIO_MODER_OUT);
    //GPIO_MODER_SET(LED_RED, GPIO_MODER_OUT);
    //GPIO_MODER_SET(LED_GREEN, GPIO_MODER_OUT);


	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT,
						GPIO_PUPD_NONE, GPIO12 | GPIO13 | GPIO14 | GPIO15);


    // endless loop
    while(1) {

        //GPIO_BSRR_SET(LED_ORANGE);
        //GPIO_BSRR_SET(LED_RED);
        //GPIO_BSRR_RESET(LED_BLUE);
        //GPIO_BSRR_RESET(LED_GREEN);
		gpio_set(GPIOD, GPIO12|GPIO14);
		gpio_clear(GPIOD, GPIO13|GPIO15);
        ITM_putc('A');

        for (i = 0; i < 6000000; i++)
            __asm__("nop");

        //GPIO_BSRR_RESET(LED_ORANGE);
        //GPIO_BSRR_RESET(LED_RED);
        //GPIO_BSRR_SET(LED_BLUE);
        //GPIO_BSRR_SET(LED_GREEN);
		gpio_toggle(GPIOD, GPIO12 | GPIO13 | GPIO14 | GPIO15);
		ITM_puts("Caca\n");

        for (i = 0; i < 6000000; i++)
            __asm__("nop");
    }
}
