#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>		// for file structure
#include<linux/cdev.h> 		// for cdev structure
#include<linux/kdev_t.h> 	// for device file
#include<linux/device.h>
#include<linux/slab.h>		// for kmalloc
#include<linux/uaccess.h>	// for copy_to_user & copy_from_user
#include<linux/ioctl.h>
#include<linux/sched.h>		// for jiffies

#define DEVICE_NAME "My_IOCTL_cdd"
#define MAGICNO 'J'
#define PRINT_JIFFIES _IO(MAGICNO, 'a')
#define READ_JIFFIES _IOR(MAGICNO, 'b', unsigned long*)



dev_t dev_num;
static struct cdev my_cdev;

static long my_ioctl(struct file *filp, unsigned int cmd, unsigned long arg){
	unsigned long data = jiffies;
	pr_info("Inside IOCTL kernel\n");
	switch(cmd){
		case READ_JIFFIES:
			if(copy_to_user((unsigned long *)arg, &data, sizeof(data))){
				pr_err("Jiffies Read: Error!\n");
			}
			break;
		default:
			pr_info("Printing jiffies inside kernel..%lu\n", data);
	}
	return 0;
}

// File operation structure
static struct file_operations fops = {
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= my_ioctl,
};


static int __init chr_init(void){

	// Regestering/allocating the device number
	if(alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME) < 0){
		pr_err("Can't allocate the device number: Error!\n");
		return -1;
	}
	pr_info("Hello Kernel\n");
	pr_info("Device registerd successfully with.... Major:%d and Minor:%d\n", MAJOR(dev_num), MINOR(dev_num));

	// Initialising the device structure
	cdev_init(&my_cdev, &fops);

	
	// Adding the device into the device table of the kernel
	if(cdev_add(&my_cdev, dev_num, 1) < 0){
		pr_err("cdev_add() failed: Error\n");
		return -1;
	}
	return 0;

}


static void __exit chr_exit(void){
	// Un-regestering/un-allocating the device number
	unregister_chrdev_region(dev_num, 1);
	pr_info("Device un-registered successfully !! Byee Kernel\n");
}


// init & exit macros
module_init(chr_init);
module_exit(chr_exit);


// license
MODULE_LICENSE("GPL");
MODULE_AUTHOR("JST");
MODULE_DESCRIPTION("Testing ioclt operations to read jiffies from kernel-space & print into user-space");
