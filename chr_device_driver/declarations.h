#define DEVICE_NAME "myCDD"
#define BUFFER_SIZE 256 // bytes


dev_t device_id;
static struct cdev my_cdev; 

int my_open(struct inode *, struct file *);
int my_release(struct inode *, struct file *);
ssize_t my_read(struct file *, char __user *, size_t, loff_t *);
ssize_t my_write(struct file *, const char __user *, size_t, loff_t *);


MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "Jay Shakti" );
MODULE_DESCRIPTION( "Char Device Driver with the read, write, open, close operations" );
