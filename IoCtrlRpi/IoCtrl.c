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
#include <asm/system.h>
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

static int IoCtrl_init(void)
{
	int result;
	int i;

	dev_t devno = MKDEV(IoCtrl_major,0);

	if (IoCtrl_major)
	{
		/*静态申请设备号*/
		result = register_chrdev_region(devno,2,"IoCtrl");
	}else
	{
		/*动态申请设备号*/
		result = alloc_chrdev_region(&devno,0,2,"IoCtrl");
		IoCtrl_major = MAJOR(devno);
	}
	
	if (result<0)
	{
		printk(KERN_INFO"allow devno fail \n");
		return result;
	}	
	/*初始化cdev结构*/
	cdev_init(&cdev,&IoCtrl_fops);
	cdev.owner = THIS_MODULE;
	cdev.ops = &IoCtrl_fops;
	
	/*注册字符设备*/
	cdev_add(&cdev, MKDEV(IoCtrl_major, 0), IOCTRL_NR_DEVS);
	
	/*映射GPIO地址*/
	bcm2835_gpio = (volatile uint32_t *)ioremap(BCM2835_GPIO_ADDRESS_START, BCM2835_GPIO_ADDRESS_LEN);
	if(!bcm2835_gpio)
	{	
		printk(KERN_INFO"gpio map fail \n");
		unregister_chrdev_region(devno,1);
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
	cdev_del(&cdev); 
	unregister_chrdev_region(MKDEV(IoCtrl_major,0),2);
	
	printk("loCtrl device uninstalled\n");
}

MODULE_AUTHOR("Spice");
MODULE_LICENSE("GPL");

module_init(IoCtrl_init);
module_exit(IoCtrl_exit);

