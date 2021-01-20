#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include "usb_cdc_helper.h"

/* Set STM32 to 168 MHz. */
static void clock_setup(void)
{
	rcc_clock_setup_pll(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);

	/* Enable GPIOD clock. */
	rcc_periph_clock_enable(RCC_GPIOD);

}

static void gpio_setup(void)
{
	/* Set GPIO12-15 (in GPIO port D) to 'output push-pull'. */
	gpio_mode_setup(GPIOD, GPIO_MODE_OUTPUT,
			GPIO_PUPD_NONE, GPIO12 | GPIO13 | GPIO14 | GPIO15);

}

int main(void)
{
	int i;

	clock_setup();
	gpio_setup();

	/* Set two LEDs for wigwag effect when toggling. */


	/* USB CDC initialization */

	usbd_device *usbd_dev;

	rcc_clock_setup_pll(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);

	rcc_periph_clock_enable(RCC_GPIOA);
	rcc_periph_clock_enable(RCC_OTGFS);

	gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO11 | GPIO12);
	gpio_set_af(GPIOA, GPIO_AF10, GPIO11 | GPIO12);

	usbd_dev = usbd_init(&otgfs_usb_driver, &dev, &config,
			usb_strings, 3,
			usbd_control_buffer, sizeof(usbd_control_buffer));

	usbd_register_set_config_callback(usbd_dev, cdcacm_set_config);


	gpio_set(GPIOD, GPIO14);


	// ZHEN: I do not know why yet but 
	// voir libopencm3/lib/usb/usb_dwc_common.c pour l'implementation
	for (i = 0; i < 600000; i++) { /* Wait a bit. */
		usbd_poll(usbd_dev);
		__asm__("nop");
	}

	gpio_set(GPIOD, GPIO12 | GPIO14);
	/* Blink the LEDs (PD12, PD13, PD14 and PD15) on the board. */
	while (1) {

		usbd_poll(usbd_dev);
		/* Toggle LEDs. */
		gpio_toggle(GPIOD, GPIO12 | GPIO13 | GPIO14 | GPIO15);
		for (i = 0; i < 600000; i++) { /* Wait a bit. */
			__asm__("nop");
		}
		char buf[15] = "Hello World!\n";
		while (usbd_ep_write_packet(usbd_dev, 0x82, buf, 13) == 0);
		usbd_poll(usbd_dev);
	}
	return 0;

}
