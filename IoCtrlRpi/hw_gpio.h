#ifndef __HW_GPIO_H
#define __HW_GPIO_H

#define PIN									26 //GPIO26 
#define BCM2835_GPIO_ADDRESS_START			0x3f200000
#define BCM2835_GPIO_ADDRESS_END			0x3f2000b3
#define BCM2835_GPIO_ADDRESS_LEN			(BCM2835_GPIO_ADDRESS_END - BCM2835_GPIO_ADDRESS_START)
#define BCM2835_GPSET0						0x001c
#define BCM2835_GPFSEL0						0x0000
#define BCM2835_GPCLR0						0x0028
#define BCM2835_GPIO_FSEL_OUTP				0x01
#define BCM2835_GPIO_FSEL_INP				0x00

int bcm2835_gpio_fsel(uint8_t pin, uint8_t mode);
int bcm2835_gpio_set(uint8_t pin);
int bcm2835_gpio_clr(uint8_t pin);
#endif /*__HW_GPIO_H*/
