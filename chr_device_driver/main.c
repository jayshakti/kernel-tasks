#include"headers.h"
#include"declarations.h"
#include"fileOperations.h"

char *ker_buff;
int my_open(struct inode *inode, struct file *filp){

	// creating physical memory
	if((ker_buff = kmalloc(KER_SIZE, GFP_KERNEL)) == NULL){
		pr_err("kmalloc() failed: Error");
		return -1;
	}
	pr_info("Device file opened\n");
	return 0;
}

int my_release(struct inode *inode, struct file *filp){
	
	// releasing physical memory
	kfree(ker_buff);
	pr_info("Device file closed\n");
	return 0;
}

ssize_t my_read(struct file *filp, char __user *buff, size_t len, loff_t *lfpos){
	if(copy_to_user(buff, ker_buff, KER_SIZE) != 0){
		pr_err("copy_to_user() failed: Error");
	}
	pr_info("Data read from device\n");
	return KER_SIZE;
}

ssize_t my_write(struct file *filp, const char __user *buff, size_t len, loff_t *lfpos){
	if(copy_from_user(ker_buff, buff, len) != 0 ){
		pr_err("copy_from_user() failed: Error");
	}
	pr_info("Data written to the device: %s\n", ker_buff);
	return len;
}


static int __init helloKernel_init(void){
	pr_info("Hello Kernel\n");

	//Allocating the device number
	if(alloc_chrdev_region(&device_id, 0, 1, DEVICE_NAME) < 0){
		pr_err("Can't allocate device: Errro!\n");
	}
	pr_info("Device registered successfully with...Major=%d & Minor=%d\n", MAJOR(device_id), MINOR(device_id));

	// Initialising the device structure
	cdev_init(&my_cdev, &fops);

	//Adding the device into kernel device table
	if(cdev_add(&my_cdev, device_id, 1) < 0){
		pr_err("cdev_add() failed: Error!\n");
		return -1;
	}
	return 0;
}


static void __exit helloKernel_exit(void){
	
	//Un-allocating device number
	unregister_chrdev_region(device_id, 1);
	pr_info("Device un-registered successfully !! Byee Byee Kernel\n");
}


// init & exit
module_init(helloKernel_init);
module_exit(helloKernel_exit);

