#include<linux/init.h>
#include<linux/module.h>
#include<linux/sched.h>
#include<linux/timer.h>

#define TIMEOUT 5000 // milliseconds

static struct timer_list chr_timer;
unsigned int i = 0;

// timer callback function which is called when timer expires
void callback(struct timer_list *timer){
	pr_info("inside timer callback function [%d]\n", i++);

	//re-enable the timer which will make this as a periodic timer
	mod_timer(timer, msecs_to_jiffies(TIMEOUT));
}

static int __init my_jiffies_init(void){
	pr_info("********* jiiffies thread created successfully ************\n");

	//timer setup to call the timer callback function
	timer_setup(&chr_timer, callback, 0);

	//modifying the timer based on TIMEOUT macro
	mod_timer(&chr_timer, jiffies + msecs_to_jiffies(TIMEOUT));
	return 0;
}

static void __exit my_jiffies_exit(void){
	del_timer(&chr_timer);
	pr_info("********* jiiffies thread deleted successfully ************\n");
}
// init & exit
module_init(my_jiffies_init);
module_exit(my_jiffies_exit);


// license
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Me");
MODULE_DESCRIPTION("A thread which prints kernel jiffies");

