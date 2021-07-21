struct file_operations fops = {

        open: my_open,
        write: my_write,
        read: my_read,
        release: my_release,
};


