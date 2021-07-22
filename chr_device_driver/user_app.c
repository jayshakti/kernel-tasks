#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

#define BUFFER_LIMIT 128

static int fd = -1;
void open_dev(void){
	fd = open("./dev/myNODE", O_RDWR);
	if(fd < 0){
		perror("open");
	}
	printf("Device opened successfully\n");
}
void close_dev(void){
	if(fd > 2){
		close(fd);
		printf("Device released successfully\n");
	}
	printf("Nothing to close\n");
}
void read_from_dev(void){
	char buff[BUFFER_LIMIT];
	memset(buff, '\0', sizeof(buff));
	int ret = read(fd, buff, BUFFER_LIMIT);
	if(ret < 0){
		perror("read");
	}
	printf("%s\n", buff);
	printf("Read %d bytes\n",ret);
}
void write_to_dev(void){
	char buff[BUFFER_LIMIT];
	memset(buff, '\0', sizeof(buff));
	printf("Start writing: ");
	fgets(buff, BUFFER_LIMIT, stdin);
	int ret = write(fd, buff, sizeof(buff));
	if(ret < 0){
		perror("write");
	}
	printf("\nWrote %d bytes\n",ret);
}

int main(){


	printf("%s: Welcome to the application\n", __func__);
	int ch;
	void (*func_ptr[])(void) = {open_dev, close_dev, write_to_dev, read_from_dev};
	while(1){
	
		printf("\n####### OPTIONS ########\n");
		printf("1.open\n2.close\n3.write\n4.read\n0.exit\nEnter your choice: ");
		scanf("%d",&ch);
		if(ch == 0){
			exit(EXIT_SUCCESS);
		}
		if(ch >= 1 && ch <= 4){
			(*func_ptr[ch-1])();
		}
		else{
			continue;
		}
	}
	printf("Application Ends...\n");
	return 0;
}
