#include "hw_reg.h"
#include "hw_gpio.h"

volatile unsigned int*  bcm_gpio;

static void bcm_gpio_register_write_nb(volatile unsigned int* pAddr,unsigned int value);
static void bcm_gpio_register_write(volatile unsigned int* pAddr,unsigned int value);
static unsigned int bcm_gpio_register_read(volatile unsigned int* pAddr);
static unsigned int bcm_gpio_register_read(volatile unsigned int* pAddr);
static void bcm_gpio_set_bits(volatile unsigned int pAddr,unsigned int value,unsigned int mask);

static void bcm_gpio_register_write_nb(volatile unsigned int* pAddr,unsigned int value)
{
	*pAddr = value;
}

static void bcm_gpio_register_write(volatile unsigned int* pAddr,unsigned int value)
{
	__sync_synchronize();
	*pAddr = value;
	__sync_synchronize();
}

static unsigned int bcm_gpio_register_read_nb(volatile unsigned int* pAddr)
{
	return *pAddr;
}

static unsigned int bcm_gpio_register_read(volatile unsigned int* pAddr)
{
	unsigned int ret;

	__sync_synchronize();
	ret = *pAddr;
	__sync_synchronize();
	return ret;
}

static void bcm_gpio_set_bits(volatile unsigned int pAddr,unsigned int value,unsigned int mask)
{
	unsigned int val = bcm_gpio_register_read(pAddr);

	val = (val&~mask) | (value & mask);

	bcm_gpio_register_write(pAddr,val);
}

void bcm_gpio_fsel(unsigned char pin, unsigned char mode)
{
    volatile unsigned int* paddr = bcm_gpio + BCM_GPFSEL0/4 + (pin/10);
    unsigned char   shift = (pin % 10) * 3;
    unsigned int  mask = BCM_GPIO_FSEL_MASK << shift;
    unsigned int  value = mode << shift;
    bcm_gpio_set_bits(paddr, value, mask);
}

void bcm_gpio_set(unsigned char pin)
{
    volatile unsigned int* paddr = bcm_gpio + BCM_GPSET0/4 + pin/32;
    unsigned char shift = pin % 32;
    bcm_gpio_register_write(paddr, 1 << shift);
}

void bcm_gpio_clr(unsigned char pin)
{
    volatile unsigned int* paddr = bcm_gpio + BCM_GPCLR0/4 + pin/32;
    unsigned char shift = pin % 32;
    bcm_gpio_register_write(paddr, 1 << shift);
}
