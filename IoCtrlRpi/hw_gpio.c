#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/io.h>
#include <linux/miscdevice.h>
//#include <asm/system.h>
#include <asm/uaccess.h>

#include "hw_gpio.h"

unsigned long * bcm2835_gpio;

int bcm2835_gpio_fsel(unsigned char pin, unsigned char mode)
{
	volatile unsigned long * bcm2835_gpio_fsel = bcm2835_gpio + BCM2835_GPFSEL0/4 + (pin/10);
	unsigned char   shift = (pin % 10) * 3;
	unsigned long  value = mode << shift;
	*bcm2835_gpio_fsel = *bcm2835_gpio_fsel | value;
	return 0;
}

int bcm2835_gpio_set(unsigned char pin)
{
	volatile unsigned long * bcm2835_gpio_set = bcm2835_gpio + BCM2835_GPSET0/4 + pin/32;
	unsigned char   shift = pin % 32;
	unsigned long  value = 1 << shift;
	*bcm2835_gpio_set = *bcm2835_gpio_set | value;


	return 0;
}

int bcm2835_gpio_clr(unsigned char pin)
{
	volatile unsigned long * bcm2835_gpio_clr = bcm2835_gpio + BCM2835_GPCLR0/4 + pin/32;
	unsigned char   shift = pin % 32;
	unsigned long  value = 1 << shift;
	*bcm2835_gpio_clr = *bcm2835_gpio_clr | value;


	return 0;
}