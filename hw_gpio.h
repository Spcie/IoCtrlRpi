#ifndef __HW_GPIO_H
#define __HW_GPIO_H

#define PIN					26 //GPIO26 
#define BCM2835_GPIO_ADDRESS_START           0x3f200000
#define BCM2835_GPIO_ADDRESS_END             0x3f2000b3
#define BCM2835_GPIO_ADDRESS_LEN             (BCM2835_GPIO_ADDRESS_END - BCM2835_GPIO_ADDRESS_START)
#define BCM2835_GPSET0                       0x001c  
#define BCM2835_GPFSEL0                      0x0000  
#define BCM2835_GPCLR0                       0x0028  
#define BCM2835_GPIO_FSEL_OUTP               1  
  


#endif /*__HW_GPIO_H*/
