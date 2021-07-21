#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>		// for file structure
#include<linux/cdev.h> 		// for cdev structure
#include<linux/kdev_t.h> 	// for device file
#include<linux/device.h>
#include<linux/slab.h>		// for kmalloc
#include<linux/uaccess.h>	// for copy_to_user & copy_from_user

#define DEVICE_NAME "My_LKM_cdd"

// license
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jay Shakti Tripathi");
MODULE_DESCRIPTION("Testing cdd along with read, write, open, close & ioclt operations");


dev_t dev_num;
static int __init cdd_init(void){

	// Regestering/allocating the device number
	if(alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME) < 0){
		pr_info("Can't allocate the device number\n");
		return -1;
	}
	pr_info("Device registerd successfully with.... Major:%d and Minor:%d\n", MAJOR(dev_num), MINOR(dev_num));
	return 0;

}


static void __exit cdd_exit(void){
	// Un-regestering/un-allocating the device number
	unregister_chrdev_region(dev_num, 1);
	pr_info("Device un-registered successfully !! Byee Kernel\n");
}


// init & exit macros
module_init(cdd_init);
module_exit(cdd_exit);


