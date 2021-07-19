#include<linux/module.h>

static int __init my_jiffies_init(void){
	pr_info("Jiffies\n");
	return 0;
}

static void __exit my_jiffies_exit(void){
	pr_info("Byee\n");
}
// init & exit
module_init(my_jiffies_init);
module_exit(my_jiffies_exit);


// license
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Me");
MODULE_DESCRIPTION("A thread which prints kernel jiffies");

