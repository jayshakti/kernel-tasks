
#include<linux/module.h>

static int __init helloKernel_init(void){
	pr_info("Hello Kernel\n");
	return 0;
}

static void __exit helloKernel_exit(void){
	pr_info("Byee Byee Kernel\n");
}

// init & exit
module_init(helloKernel_init);
module_exit(helloKernel_exit);


// license
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Me");
MODULE_DESCRIPTION("Testing CDD to print kernel logs on the host machine");

