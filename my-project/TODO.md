The current status:
	1.	The Hello World in main loop seems to print correctely.
	2.	The usbd_poll is called before the main loop, otherwise, the device is not even regonized.
	3.	I do not know exactly what poll does, but is it in libopencm3/lib/usb/usb_dwc_common.c, the read/write functions are also there
	4.	I think the problem is during the initialization step (called Enumeration step).
