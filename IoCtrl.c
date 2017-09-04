#include <linux/module.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <asm/io.h>
//#include <asm/system.h>
#include <asm/uaccess.h>

#include "IoCtrl.h"

static int IoCtrl_major = MEMDEV_MAJOR;

module_param(IoCtrl_major, int, S_IRUGO);

struct cdev cdev;

int IoCtrl_open(struct inode * inode,struct file *filp);
int IoCtrl_release(struct inode * inode, struct file *filp);

int IoCtrl_open(struct inode * inode,struct file *filp)
{
	struct  mem_dev *dev;

	/*获取次设备号*/
	int num = MINOR(inode->i_rdev);

	if(num >= IOCTRL_NR_DEVS) return -ENODEV;

	dev = &mem_devp[num];

	/*将设备描述符指针赋值给文件私有数据指针*/
	filp->private_data = dev;

	return 0;
}

int IoCtrl_release(struct inode * inode, struct file *filp)
{
	return 0;
}

static ssize_t IoCtrl_read(struct file *filp, char __user *buf, size_t size, loff_t *ppos)
{
	int ret = 0;

	return ret;
}

static ssize_t IoCtrl_write(struct file *filp, const char __user *buf, size_t size, loff_t *ppos)
{

	int ret = 0;


	return ret;
}

static loff_t IoCtrl_llseek(struct file *filp, loff_t offset, int whence)
{
	return 0;
}

int IoCtrl_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
	return 0;
}
static const struct file_operations mem_fops = 
{
	.owner = THIS_MODULE,
	.llseek = IoCtrl_llseek,
	.read = IoCtrl_read,
	.write = IoCtrl_write,
	.open = IoCtrl_open,
	.release = IoCtrl_release,
	.unlocked_ioctl = IoCtrl_ioctl,
};

static int IoCtrl_init(void)
{
	return 0;

}

static void IoCtrl_exit(void)
{
	cdev_del(&cdev); /*注销设备号*/
	unregister_chrdev_region(MKDEV(mem_major,0),2);
}

MODULE_AUTHOR("Spice");
MODULE_LICENSE("GPL");

module_init(IoCtrl_init);
module_exit(IoCtrl_exit);