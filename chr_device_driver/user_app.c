#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<string.h>

#define BUFF_LIMIT 128

static int fd = -1;
void open_dev(void){
	fd = open("/dev/myNODE", O_RDWR);
	if(fd < 0){
		perror("open");
	}else{
		printf("Device opened successfully: fd=%d\n",fd);
	}
}
void close_dev(void){
	if(fd > 2){
		close(fd);
		printf("Device released successfully\n");
	}
	else{
		printf("Nothing to close\n");
	}
}
void read_from_dev(void){
	char buff[BUFF_LIMIT];
	memset(buff, '\0', sizeof(buff));
	int ret = read(fd, buff, BUFF_LIMIT);
	if(ret < 0){
		perror("read");
	}
	else{
		printf("%s\n", buff);
		printf("Read %d bytes\n",ret);
	}
}
void write_to_dev(void){
	char buff[BUFF_LIMIT];
	memset(buff, '\0', sizeof(buff));
	printf("Start writing: ");
	scanf("%s",buff);
	// fgets(buff, BUFF_LIMIT, stdin);
	int ret = write(fd, buff, sizeof(buff));
	if(ret < 0){
		perror("write");
	}
	else{
		printf("\nWrote %d bytes\n",ret);
	}
}

int main(){


	printf("\n%s: Welcome to the application\n", __func__);
	open_dev(); /* opening the special file names as myNODE present /dev */
	void (*func_ptr[])(void) = {close_dev, write_to_dev, read_from_dev};
	int ch;
	while(1){
	
		printf("\n####### OPTIONS ########\n");
		printf("1.close\n2.write\n3.read\n0.exit\nEnter your choice: ");
		scanf("%d",&ch);
		if(ch == 0){
			exit(EXIT_SUCCESS);
		}
		if(ch >= 1 && ch <= 3){
			(*func_ptr[ch-1])();
		}
		else{
			continue;
		}
	}
	printf("Application Ends...\n");
	return 0;
}
