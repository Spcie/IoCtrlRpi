#ifndef __IOCTRL_H
#define __IOCTRL_H

#ifndef IOCTRL_MAJOR
#define IOCTRL_MAJOR 124
#endif

#ifndef IOCTRL_NR_DEVS
#define IOCTRL_NR_DEVS 2
#endif


/*定义幻数*/
#define IOCTRL_IOC_MAGIC 'x'

/*定义命令*/
#define IOCTRL_IOCPRINT _IO(MEMDEV_IOC_MAGIC,1)
#define IOCTRL_IOCGETDATA _IOR(MEMDEV_IOC_MAGIC,2,int)
#define IOCTRL_IOCSETDATA _IOW(MEMDEV_IOC_MAGIC,3,int)


#endif /*__IOCTRL_H*/
