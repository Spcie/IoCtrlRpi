#include "hw_gpio.h"
int bcm2835_gpio_fsel(uint8_t pin, uint8_t mode)
{
	volatile uint32_t * bcm2835_gpio_fsel = bcm2835_gpio + BCM2835_GPFSEL0/4 + (pin/10);
	uint8_t   shift = (pin % 10) * 3;
	uint32_t  value = mode << shift;
	*bcm2835_gpio_fsel = *bcm2835_gpio_fsel | value;

}

int bcm2835_gpio_set(uint8_t pin)
{
	volatile uint32_t * bcm2835_gpio_set = bcm2835_gpio + BCM2835_GPSET0/4 + pin/32;
	uint8_t   shift = pin % 32;
	uint32_t  value = 1 << shift;
	*bcm2835_gpio_set = *bcm2835_gpio_set | value;


	return 0;
}

int bcm2835_gpio_clr(uint8_t pin)
{
	volatile uint32_t * bcm2835_gpio = (volatile uint32_t *)ioremap(BCM2835_GPIO_ADDRESS_START, BCM2835_GPIO_ADDRESS_LEN);
	volatile uint32_t * bcm2835_gpio_clr = bcm2835_gpio + BCM2835_GPCLR0/4 + pin/32;
	uint8_t   shift = pin % 32;
	uint32_t  value = 1 << shift;
	*bcm2835_gpio_clr = *bcm2835_gpio_clr | value;

	printk("clr address:  0x%lx : %x\n", (long unsigned int)bcm2835_gpio_clr, *bcm2835_gpio_clr);

	return 0;
}
