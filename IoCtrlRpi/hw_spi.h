#define BCM_SPI0_CS                      0x0000 // SPI Master Control and Status
#define BCM_SPI0_FIFO                    0x0004 // SPI Master TX and RX FIFOs
#define BCM_SPI0_CLK                     0x0008 // SPI Master Clock Divider
#define BCM_SPI0_DLEN                    0x000c // SPI Master Data Length
#define BCM_SPI0_LTOH                    0x0010 // SPI LOSSI mode TOH
#define BCM_SPI0_DC                      0x0014 // SPI DMA DREQ Controls

// Register masks for SPI0_CS
#define BCM_SPI0_CS_LEN_LONG             0x02000000 // Enable Long data word in Lossi mode if DMA_LEN is set
#define BCM_SPI0_CS_DMA_LEN              0x01000000 // Enable DMA mode in Lossi mode
#define BCM_SPI0_CS_CSPOL2               0x00800000 // Chip Select 2 Polarity
#define BCM_SPI0_CS_CSPOL1               0x00400000 // Chip Select 1 Polarity
#define BCM_SPI0_CS_CSPOL0               0x00200000 // Chip Select 0 Polarity
#define BCM_SPI0_CS_RXF                  0x00100000 // RXF - RX FIFO Full
#define BCM_SPI0_CS_RXR                  0x00080000 // RXR RX FIFO needs Reading (full)
#define BCM_SPI0_CS_TXD                  0x00040000 // TXD TX FIFO can accept Data
#define BCM_SPI0_CS_RXD                  0x00020000 // RXD RX FIFO contains Data
#define BCM_SPI0_CS_DONE                 0x00010000 // Done transfer Done
#define BCM_SPI0_CS_TE_EN                0x00008000 // Unused
#define BCM_SPI0_CS_LMONO                0x00004000 // Unused 
#define BCM_SPI0_CS_LEN                  0x00002000 // LEN LoSSI enable
#define BCM_SPI0_CS_REN                  0x00001000 // REN Read Enable 
#define BCM_SPI0_CS_ADCS                 0x00000800 // ADCS Automatically Deassert Chip Select 
#define BCM_SPI0_CS_INTR                 0x00000400 // INTR Interrupt on RXR 
#define BCM_SPI0_CS_INTD                 0x00000200 // INTD Interrupt on Done 
#define BCM_SPI0_CS_DMAEN                0x00000100 // DMAEN DMA Enable 
#define BCM_SPI0_CS_TA                   0x00000080 // Transfer Active 
#define BCM_SPI0_CS_CSPOL                0x00000040 // Chip Select Polarity 
#define BCM_SPI0_CS_CLEAR                0x00000030 // Clear FIFO Clear RX and TX 
#define BCM_SPI0_CS_CLEAR_RX             0x00000020 // Clear FIFO Clear RX 
#define BCM_SPI0_CS_CLEAR_TX             0x00000010 // Clear FIFO Clear TX 
#define BCM_SPI0_CS_CPOL                 0x00000008 // Clock Polarity 
#define BCM_SPI0_CS_CPHA                 0x00000004 // Clock Phase 
#define BCM_SPI0_CS_CS                   0x00000003 // Chip Select 


typedef enum
{
    BCM_SPI0_BIT_ORDER_LSBFIRST = 0,  // LSB First 
    BCM_SPI0_BIT_ORDER_MSBFIRST = 1   // MSB First 
}bcmSPIBitOrder;


typedef enum
{
    BCM_SPI0_MODE0 = 0,  // CPOL = 0, CPHA = 0 
    BCM_SPI0_MODE1 = 1,  // CPOL = 0, CPHA = 1 
    BCM_SPI0_MODE2 = 2,  // CPOL = 1, CPHA = 0 
    BCM_SPI0_MODE3 = 3   // CPOL = 1, CPHA = 1 
}bcmSPIMode;


typedef enum
{
    BCM_SPI_CS0 = 0,     // Chip Select 0 
    BCM_SPI_CS1 = 1,     // Chip Select 1 
    BCM_SPI_CS2 = 2,     // Chip Select 2 (ie pins CS1 and CS2 are asserted) 
    BCM_SPI_CS_NONE = 3  // No CS, control it yourself 
} bcm2835SPIChipSelect;

typedef enum
{
    BCM_SPI_CLOCK_DIVIDER_65536 = 0,       // 65536 = 3.814697260kHz on Rpi2, 6.1035156kHz on RPI3 
    BCM_SPI_CLOCK_DIVIDER_32768 = 32768,   // 32768 = 7.629394531kHz on Rpi2, 12.20703125kHz on RPI3
    BCM_SPI_CLOCK_DIVIDER_16384 = 16384,   // 16384 = 15.25878906kHz on Rpi2, 24.4140625kHz on RPI3
    BCM_SPI_CLOCK_DIVIDER_8192  = 8192,    // 8192 = 30.51757813kHz on Rpi2, 48.828125kHz on RPI3 
    BCM_SPI_CLOCK_DIVIDER_4096  = 4096,    // 4096 = 61.03515625kHz on Rpi2, 97.65625kHz on RPI3 
    BCM_SPI_CLOCK_DIVIDER_2048  = 2048,    // 2048 = 122.0703125kHz on Rpi2, 195.3125kHz on RPI3 
    BCM_SPI_CLOCK_DIVIDER_1024  = 1024,    // 1024 = 244.140625kHz on Rpi2, 390.625kHz on RPI3 
    BCM_SPI_CLOCK_DIVIDER_512   = 512,     // 512 = 488.28125kHz on Rpi2, 781.25kHz on RPI3
    BCM_SPI_CLOCK_DIVIDER_256   = 256,     // 256 = 976.5625kHz on Rpi2, 1.5625MHz on RPI3 
    BCM_SPI_CLOCK_DIVIDER_128   = 128,     // 128 = 1.953125MHz on Rpi2, 3.125MHz on RPI3
    BCM_SPI_CLOCK_DIVIDER_64    = 64,      // 64 = 3.90625MHz on Rpi2, 6.250MHz on RPI3
    BCM_SPI_CLOCK_DIVIDER_32    = 32,      // 32 = 7.8125MHz on Rpi2, 12.5MHz on RPI3 
    BCM_SPI_CLOCK_DIVIDER_16    = 16,      // 16 = 15.625MHz on Rpi2, 25MHz on RPI3 
    BCM_SPI_CLOCK_DIVIDER_8     = 8,       // 8 = 31.25MHz on Rpi2, 50MHz on RPI3 
    BCM_SPI_CLOCK_DIVIDER_4     = 4,       // 4 = 62.5MHz on Rpi2, 100MHz on RPI3. Dont expect this speed to work reliably. 
    BCM_SPI_CLOCK_DIVIDER_2     = 2,       // 2 = 125MHz on Rpi2, 200MHz on RPI3, fastest you can get. Dont expect this speed to work reliably.
    BCM_SPI_CLOCK_DIVIDER_1     = 1        // 1 = 3.814697260kHz on Rpi2, 6.1035156kHz on RPI3, same as 0/65536 
} bcm2835SPIClockDivider;
