#ifndef __IOCTRL_H
#define __IOCTRL_H

#ifndef IOCTRL_MAJOR
#define IOCTRL_MAJOR 124	//混杂设备可不用
#endif

#ifndef IOCTRL_NR_DEVS
#define IOCTRL_NR_DEVS 2	//可能为1更好
#endif


/*定义幻数*/
#define IOCTRL_IOC_MAGIC 'x'

/*定义命令*/
#define IOCTRL_ON _IO(IOCTRL_IOC_MAGIC,1)
#define IOCTRL_OFF _IO(IOCTRL_IOC_MAGIC,2)


#endif /*__IOCTRL_H*/
