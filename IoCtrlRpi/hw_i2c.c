
#include "hw_i2c.h"
#include "hw_gpio.h"



static volatile unsigned int *bcm_bsc_base;

static int i2c_byte_wait_us = 0;

static void bcm_i2c_set_bits(unsigned int RegOfst,unsigned int value);
static void bcm_i2c_register_write_nb(unsigned int RegOfst,unsigned int value);
static void bcm_i2c_register_write(unsigned int RegOfst,unsigned int value);
static unsigned int bcm_i2c_register_read_nb(unsigned int RegOfst);
static unsigned int bcm_i2c_register_read(unsigned int RegOfst);
static void bcm_i2c_setSlaveAddress(unsigned char addr);
static void bcm_i2c_setClockDivider(unsigned int divider);
static void bcm_i2c_setBaudRate(unsigned int baudrate);
static void bcm_i2c_begin(void);
static void bcm_i2c_end(void);

static void bcm_i2c_register_write_nb(unsigned int RegOfst,unsigned int value)
{
	volatile unsigned int* pAddr = bcm_bsc_base + RegOfst/4;

	*pAddr = value;
}

static void bcm_i2c_register_write(unsigned int RegOfst,unsigned int value)
{
	volatile unsigned int* pAddr = bcm_bsc_base + RegOfst/4;
	
	__sync_synchronize();
	*pAddr = value;
	__sync_synchronize();

}

static unsigned int bcm_i2c_register_read_nb(unsigned int RegOfst)
{
	volatile unsigned int* pAddr = bcm_bsc_base + RegOfst/4;

	return *pAddr;
}

static unsigned int bcm_i2c_register_read(unsigned int RegOfst)
{
	unsigned int ret;
	volatile unsigned int* pAddr = bcm_bsc_base + RegOfst/4;

	__sync_synchronize();
	ret = *pAddr;
	__sync_synchronize();
	return ret;
}

static void bcm_i2c_set_bits(unsigned int RegOfst,unsigned int value,unsigned int mask)
{
	
	unsigned int val = bcm_i2c_register_read(RegOfst);

	val = (val&~mask) | (value & mask);

	bcm_i2c_register_write(RegOfst,val);
}

static void bcm_i2c_setSlaveAddress(unsigned char addr)
{
	bcm_i2c_register_write(BCM_BSC_A,addr&0x7F)
}

static void bcm_i2c_setClockDivider(unsigned int divider)
{
	bcm_peri_write(BCM_BSC_DIV, divider&0xFF);
	
	i2c_byte_wait_us = ((float)divider / BCM_CORE_CLK_HZ) *  1000000 * 9;
}

static void bcm_i2c_setBaudRate(unsigned int baudrate)
{
	unsigned int divider;
	divider = (BCM_CORE_CLK_HZ / baudrate) & 0xFFFE;

	bcm_i2c_setClockDivider( (unsigned int)divider );
}


static void bcm_i2c_begin(void)
{
	unsigned int cdiv = bcm_i2c_register_read(BCM_BSC_DIV);

	i2c_byte_wait_us = ((float)cdiv/BCM_CORE_CLK_HZ) * 1000000 * 9;
}

static void bcm_i2c_end(void)
{

}

void bcm_i2c_init(void)
{

}

void bcm_i2c_uninit(void)
{

}

void bcm_i2c_write(const char * buf, unsigned int len)
{	
	unsigned int remaining = len;
	unsigned int i = 0;

	// Clear FIFO
	bcm_i2c_set_bits(BCM_BSC_C,BCM_BSC_C_CLEAR_1,BCM_BSC_C_CLEAR_1);
	// Clear Status
	bcm_i2c_register_write(BSM_BSC_S, BCM_BSC_S_CLEAN_CLKT | BCM_BSC_S_CLEAN_ERR | BCM_BSC_S_DONE);
	// Set Data Length
	bcm_i2c_register_write(BCM_BSC_DLEN,len);
	
	//pre populate FIFO with max buffer
	while(remaining && (i < BCM_BSC_FIFO_DEPTH))
	{
		bcm_i2c_register_write_nb(BCM_BSC_FIFO, buf[i]);
		i++;
		remaining--;
	}
	
	// Enable device and start transfer
	bcm_i2c_register_write(BCM_BSC_C,BCM_BSC_C_I2CEN | BCM_BSC_C_ST);

	// Transfer is over when BCM_BSC_S_DONE
	while(!(bcm_i2c_register_read(BCM_BSC_S) & BCM_BSC_S_DONE))
	{
		while(remaining &&(bcm_i2c_register_read(BCM_BSC_S) & BCM_BSC_S_TXD))
		{
			 Write to FIFO
			bcm_i2c_register_write(BCM_BSC_FIFO, buf[i]);
			i++;
			remaining--;
		}
	}
	
	if(bcm_i2c_register_read(BCM_BSC_S) & BCM_BSC_S_ERR)
	{
		// Received a NACK
		reason = BCM_I2C_REASON_OK;
	}else if(bcm_i2c_register_read(BCM_BSC_S) & BCM_BSC_S_CLKT)
	{
		//Received Clock Stretch Timeout
		reason = BCM_I2C_REASON_ERROR_CLKT;
	}else if(remaining)
	{
		//not all data is sent
		reason = BCM_I2C_REASON_ERROR_DATA;
	}

	bcm_i2c_set_bits(BSM_BSC_S, BCM_BSC_S_DONE, BCM_BSC_S_DONE);

	return reason;
}

void bcm_i2c_read(char * buf, unsigned int len)
{
	unsigned int i = 0;
	unsigned int remaining = len;
	unsigned char reason;

	// Clear FIFO
	bcm_i2c_set_bits(BCM_BSC_C,BCM_BSC_C_CLEAR_1,BCM_BSC_C_CLEAR_1);
	// Clear Status
	bcm_i2c_register_write_nb(BSM_BSC_S, BCM_BSC_S_CLEAN_CLKT | BCM_BSC_S_CLEAN_ERR | BCM_BSC_S_DONE);
	// Set Data Length
	bcm_i2c_register_write_nb(BCM_BSC_DLEN,len);
	// Start read
	bcm_i2c_register_write_nb(BSM_BSC_S, BCM_BSC_C_I2CEN | BCM_BSC_C_ST | BCM_BSC_C_READ);

	// wait for transfer to complete
	while(!(bcm_i2c_register_read_nb(BCM_BSC_S) & BCM_BSC_S_DONE))
	{
		//we must empty the FIFO as it is populated and not use any delay 
		while(bcm_i2c_register_read_nb(BCM_BSC_S) & BCM_BSC_S_RXD)
		{
			//Read from FIFO, no barrier
			buf[i] = bcm_i2c_register_read_nb(BCM_BSC_FIFO);
			i++;
			remaining--;
		}
	}

	//transfer has finished - grab any remaining stuff in FIFO
	while(remaining && (bcm_i2c_register_read_nb(BCM_BSC_S) & BCM_BSC_S_RXD))
	{
			buf[i] = bcm_i2c_register_read_nb(BCM_BSC_FIFO);
			i++;
			remaining--;
	}


	if (bcm_i2c_register_read(BCM_BSC_S) & BCM_BSC_S_ERR)
	{
		//Received a NACK
		reason = BCM_I2C_REASON_OK;
	}
	else if(bcm_i2c_register_read(BCM_BSC_S) & BCM_BSC_S_CLKT)
	{
		//Received Clock Stretch Timeout 
		reason = BCM_I2C_REASON_ERROR_CLKT;
	}else if(remaining)
	{
		//Not all data is received
		reason = BCM_I2C_REASON_ERROR_DATA;
	}
	
	bcm_i2c_set_bits(BSM_BSC_S, BCM_BSC_S_DONE, BCM_BSC_S_DONE);
	
	return reason;
}

