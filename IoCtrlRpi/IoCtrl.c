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

#include "IoCtrl.h"
#include "hw_gpio.h"

static int IoCtrl_major = IOCTRL_MAJOR;

module_param(IoCtrl_major, int, S_IRUGO);

struct cdev cdev;

int IoCtrl_open(struct inode * inode,struct file *filp);
int IoCtrl_release(struct inode * inode, struct file *filp);

int IoCtrl_open(struct inode * inode,struct file *filp)
{
	return 0;
}

int IoCtrl_release(struct inode * inode, struct file *filp)
{
	return 0;
}

static ssize_t IoCtrl_read(struct file *filp, char __user *buf, size_t size, loff_t *ppos)
{
	int ret = 0;
	bcm2835_gpio_fsel(PIN,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_clr(PIN);

	return ret;
}

static ssize_t IoCtrl_write(struct file *filp, const char __user *buf, size_t size, loff_t *ppos)
{

	int ret = 0;

	bcm2835_gpio_fsel(PIN,BCM2835_GPIO_FSEL_OUTP);
	bcm2835_gpio_set(PIN);
	return ret;
}

static loff_t IoCtrl_llseek(struct file *filp, loff_t offset, int whence)
{
	return 0;
}

long IoC_ioctl(struct file*filp,unsigned int cmd,unsigned long arg)
{
	
	switch(cmd)
	{
		case IOCTRL_ON : break;
		case IOCTRL_OFF : break;
		default:
			return -EINVAL;
	}
	
	return 0;
}
static const struct file_operations IoCtrl_fops = 
{
	.owner = THIS_MODULE,
	.llseek = IoCtrl_llseek,
	.read = IoCtrl_read,
	.write = IoCtrl_write,
	.open = IoCtrl_open,
	.release = IoCtrl_release,
	.unlocked_ioctl = IoC_ioctl,
};
struct miscdevice misc_dev =
{
	.minor = 50,
	.fops = &IoCtrl_fops,
	.name = "msic_IoCtrl"
};

static int IoCtrl_init(void)
{
	int result;

	printk("----- misc test init-----\n");
	result = misc_register(&misc_dev);
	/*映射GPIO地址*/
	bcm2835_gpio = (volatile unsigned long *)ioremap(BCM2835_GPIO_ADDRESS_START, BCM2835_GPIO_ADDRESS_LEN);
	if(!bcm2835_gpio)
	{	
		printk(KERN_INFO"gpio map fail \n");
		return -EIO;
	}

	printk("loCtrl device installed\n");
	return 0;

}

static void IoCtrl_exit(void)
{
	/*取消映射*/
	iounmap(bcm2835_gpio);
	
	/*注销设备号*/
	misc_deregister(&misc_dev);
	
	printk("loCtrl device uninstalled\n");
}

MODULE_AUTHOR("Spice");
MODULE_LICENSE("GPL");

module_init(IoCtrl_init);
module_exit(IoCtrl_exit);

