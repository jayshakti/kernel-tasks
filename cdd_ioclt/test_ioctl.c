#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/ioctl.h>
#include<fcntl.h>


#define MAGICNO 'J'
#define PRINT_JIFFIES _IO(MAGICNO, 'a')
#define READ_JIFFIES _IOR(MAGICNO, 'b', unsigned long*)

int main(){
	int fd, ch;
	unsigned long jiff = 0;
	fd = open("/dev/chr_IOCTL",O_RDWR);
	if(fd < 0){
		perror("open");
		printf("File can't be opened fd=%d\n", fd);
		return -1;
	}
	printf("Application Begins: %s\n", __FILE__);
	while(1){
		printf("Press 1. to get jiffies from kernel-space into user-space\n");
		printf("Press 2. to print jiffies in kernel space\n");
		printf("Press 3. to exit from application\n");
		scanf("%d", &ch);
		if(ch == 1){
			ioctl(fd, READ_JIFFIES, &jiff);
			printf("Jiffies value: %lu\n", jiff);
		}
		else if(ch == 2){
			ioctl(fd, PRINT_JIFFIES);
		}
		else{
			break;
		}
	}
	printf("Application Closed: %s\n", __FILE__);
	close(fd);
	return 0;

}
