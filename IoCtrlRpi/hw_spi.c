

volatile unsigned int* bcm_spi0_base;

static void bcm_spi0_register_write_nb(unsigned int RegOfst,unsigned int value);
static void bcm_spi0_register_write(unsigned int RegOfst,unsigned int value);
static unsigned int bcm_spi0_register_read_nb(unsigned int RegOfst);
static unsigned int bcm_spi0_register_read(unsigned int RegOfst);
static void bcm_spi0_set_bits(unsigned int RegOfst,unsigned int value,unsigned int mask);
static void bcm_spi0_setClockDivider(unsigned int divider);
static void bcm_spi0_setDataMode(unsigned int mode);
static void bcm_spi0_chipSelect(unsigned int cs);
static void bcm2835_spi_setChipSelectPolarity(unsigned int cs, unsigned int active);



static void bcm_spi0_register_write_nb(unsigned int RegOfst,unsigned int value)
{
	volatile unsigned int* pAddr = bcm_spi0_base + RegOfst/4;

	*pAddr = value;
}

static void bcm_spi0_register_write(unsigned int RegOfst,unsigned int value)
{
	volatile unsigned int* pAddr = bcm_spi0_base + RegOfst/4;
	
	__sync_synchronize();
	*pAddr = value;
	__sync_synchronize();

}

static unsigned int bcm_spi0_register_read_nb(unsigned int RegOfst)
{
	volatile unsigned int* pAddr = bcm_spi0_base + RegOfst/4;

	return *pAddr;
}

static unsigned int bcm_spi0_register_read(unsigned int RegOfst)
{
	unsigned int ret;
	volatile unsigned int* pAddr = bcm_spi0_base + RegOfst/4;

	__sync_synchronize();
	ret = *pAddr;
	__sync_synchronize();
	return ret;
}

static void bcm_spi0_set_bits(unsigned int RegOfst,unsigned int value,unsigned int mask)
{
	
	unsigned int val = bcm_spi0_register_read(RegOfst);

	val = (val&~mask) | (value & mask);

	bcm_spi0_register_write(RegOfst,val);
}


static void bcm_spi0_setClockDivider(unsigned int divider)
{
	bcm_spi0_register_write(BCM_SPI0_CLK, divider);
}

static void bcm_spi0_setDataMode(unsigned int mode)
{
	bcm_spi0_set_bits(BCM_SPI0_CS, mode << 2, BCM_SPI0_CS_CPOL | BCM_SPI0_CS_CPHA);
}


static void bcm_spi0_chipSelect(unsigned int cs)
{
	bcm_spi0_set_bits(BCM_SPI0_CS, cs, BCM_SPI0_CS_CS);
}

static void bcm2835_spi_setChipSelectPolarity(unsigned int cs, unsigned int active)
{
    unsigned int shift = 21 + cs;
    /* Mask in the appropriate CSPOLn bit */
    bcm_spi0_set_bits(BCM2835_SPI0_CS, active << shift, 1 << shift);
}

void bcm_spi_begin(void)
{

}
void bcm_spi_end(void)
{

}
//Writes (and reads) a single byte to SPI
unsigned char bcm_spi0_transfer_byte(unsigned char data)
{
	unsigned char Rec;

	//clear FIFO TX  RX 
	bcm_spi0_set_bits(BCM_SPI0_CS, BCM_SPI0_CS_CLEAR, BCM_SPI0_CS_CLEAR);

	//set TA = 1
	bcm_spi0_set_bits(BCM_SPI0_CS, BCM_SPI0_CS_TA, BCM_SPI0_CS_TA);

	//wait TXD = 1; FIFO can rec
	while(bcm_spi0_register_read(BCM_SPI0_CS) & BCM_SPI0_CS_TXD);

	//write data to FIFO
	bcm_spi0_register_write_nb(BCM_SPI0_FIFO, data);

	//Wait for DONE to be set(transfer done)
	while(!(bcm_spi0_register_read(BCM_SPI0_CS) & BCM_SPI0_CS_DONE));

	//read FIFO
	Rec = bcm_spi0_register_read_nb(BCM_SPI0_FIFO);

	// set TA = 0
	bcm_spi0_set_bits(BCM_SPI0_CS, 0, BCM_SPI0_CS_TA);

	return Rec;
}

//Writes (and reads) an number of bytes to SPI
void bcm_spi0_transfer(char* tbuf, char* rbuf, unsigned len)
{
	unsigned int TXCnt = 0;
	unsigned int RXCnt = 0;
	
	//clear FIFO TX  RX 
	bcm_spi0_set_bits(BCM_SPI0_CS, BCM_SPI0_CS_CLEAR, BCM_SPI0_CS_CLEAR);

	//set TA = 1
	bcm_spi0_set_bits(BCM_SPI0_CS, BCM_SPI0_CS_TA, BCM_SPI0_CS_TA);

	while((TXCnt < len) || (RXCnt < len))
	{
		while((bcm_spi0_register_read(BCM_SPI0_CS) & BCM_SPI0_CS_TXD) && (TXCnt < len))
		{
			bcm_spi0_register_write_nb(BCM_SPI0_FIFO, tbuf[TXCnt]);
			TXCnt++;
		}

		while((bcm_spi0_register_read(BCM_SPI0_CS) & BCM_SPI0_CS_RXD) && (RXCnt < len))
		{
			rbuf[RXCnt] = bcm_spi0_register_read_nb(BCM_SPI0_FIFO);
			RXCnt++;
		}
	}

	//Wait for DONE to be set(transfer done)
	while(!(bcm_spi0_register_read(BCM_SPI0_CS) & BCM_SPI0_CS_DONE));

	// set TA = 0
	bcm_spi0_set_bits(BCM_SPI0_CS, 0, BCM_SPI0_CS_TA);
}

void bcm_spi0_write(char* tbuf, unsigned len)
{
	unsigned int i = 0;

	//clear FIFO TX  RX 
	bcm_spi0_set_bits(BCM_SPI0_CS, BCM_SPI0_CS_CLEAR, BCM_SPI0_CS_CLEAR);

	//set TA = 1
	bcm_spi0_set_bits(BCM_SPI0_CS, BCM_SPI0_CS_TA, BCM_SPI0_CS_TA);

	for(i = 0; i < len; i++)
	{
		//wait for TXD
		while(!(bcm_spi0_register_read(BCM_SPI0_CS) & BCM_SPI0_CS_TXD));

		bcm_spi0_register_write_nb(BCM_SPI0_FIFO, tbuf[i]);

		//wait for RXD
		while(bcm_spi0_register_read(BCM_SPI0_CS) & BCM_SPI0_CS_RXD)
		{
			bcm_spi0_register_read_nb(BCM_SPI0_FIFO);
		}
	}

	while(!(bcm_spi0_register_read(BCM_SPI0_CS) & BCM_SPI0_CS_DONE))
	{
		while(bcm_spi0_register_read(BCM_SPI0_CS) & BCM_SPI0_CS_RXD)
		{
			bcm_spi0_register_read_nb(BCM_SPI0_FIFO);
		}
	}

	// set TA = 0
	bcm_spi0_set_bits(BCM_SPI0_CS, 0, BCM_SPI0_CS_TA);
}
