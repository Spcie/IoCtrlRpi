#ifndef __HW_GPIO_H
#define __HW_GPIO_H



#define BCM_GPFSEL0                      0x0000 // GPIO Function Select 0
#define BCM_GPFSEL1                      0x0004 // GPIO Function Select 1
#define BCM_GPFSEL2                      0x0008 // GPIO Function Select 2
#define BCM_GPFSEL3                      0x000c // GPIO Function Select 3
#define BCM_GPFSEL4                      0x0010 // GPIO Function Select 4
#define BCM_GPFSEL5                      0x0014 // GPIO Function Select 5
#define BCM_GPSET0                       0x001c // GPIO Pin Output Set 0
#define BCM_GPSET1                       0x0020 // GPIO Pin Output Set 1
#define BCM_GPCLR0                       0x0028 // GPIO Pin Output Clear 0
#define BCM_GPCLR1                       0x002c // GPIO Pin Output Clear 1
#define BCM_GPLEV0                       0x0034 // GPIO Pin Level 0
#define BCM_GPLEV1                       0x0038 // GPIO Pin Level 1
#define BCM_GPEDS0                       0x0040 // GPIO Pin Event Detect Status 0
#define BCM_GPEDS1                       0x0044 // GPIO Pin Event Detect Status 1
#define BCM_GPREN0                       0x004c // GPIO Pin Rising Edge Detect Enable 0
#define BCM_GPREN1                       0x0050 // GPIO Pin Rising Edge Detect Enable 1
#define BCM_GPFEN0                       0x0058 // GPIO Pin Falling Edge Detect Enable 0
#define BCM_GPFEN1                       0x005c // GPIO Pin Falling Edge Detect Enable 1
#define BCM_GPHEN0                       0x0064 // GPIO Pin High Detect Enable 0
#define BCM_GPHEN1                       0x0068 // GPIO Pin High Detect Enable 1
#define BCM_GPLEN0                       0x0070 // GPIO Pin Low Detect Enable 0
#define BCM_GPLEN1                       0x0074 // GPIO Pin Low Detect Enable 1
#define BCM_GPAREN0                      0x007c // GPIO Pin Async. Rising Edge Detect 0
#define BCM_GPAREN1                      0x0080 // GPIO Pin Async. Rising Edge Detect 1
#define BCM_GPAFEN0                      0x0088 // GPIO Pin Async. Falling Edge Detect 0
#define BCM_GPAFEN1                      0x008c // GPIO Pin Async. Falling Edge Detect 1
#define BCM_GPPUD                        0x0094 // GPIO Pin Pull-up/down Enable
#define BCM_GPPUDCLK0                    0x0098 // GPIO Pin Pull-up/down Enable Clock 0
#define BCM_GPPUDCLK1                    0x009c // GPIO Pin Pull-up/down Enable Clock 1


typedef enum
{
    BCM_GPIO_FSEL_INPT  = 0x00,   // Input 0b000 */
    BCM_GPIO_FSEL_OUTP  = 0x01,   // Output 0b001 */
    BCM_GPIO_FSEL_ALT0  = 0x04,   // Alternate function 0 0b100 */
    BCM_GPIO_FSEL_ALT1  = 0x05,   // Alternate function 1 0b101 */
    BCM_GPIO_FSEL_ALT2  = 0x06,   // Alternate function 2 0b110, */
    BCM_GPIO_FSEL_ALT3  = 0x07,   // Alternate function 3 0b111 */
    BCM_GPIO_FSEL_ALT4  = 0x03,   // Alternate function 4 0b011 */
    BCM_GPIO_FSEL_ALT5  = 0x02,   // Alternate function 5 0b010 */
    BCM_GPIO_FSEL_MASK  = 0x07    // Function select bits mask 0b111 */
} bcmFunctionSelect;

void bcm_gpio_fsel(unsigned char pin, unsigned char mode);
void bcm_gpio_set(unsigned char pin);
void bcm_gpio_clr(unsigned char pin);
#endif /*__HW_GPIO_H*/
