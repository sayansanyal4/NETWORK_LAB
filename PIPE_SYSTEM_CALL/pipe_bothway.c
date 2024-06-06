#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
void main(){
	int fd1[2],fd2[2];
	char message[1024],buffer[1024];
	int pid=0;
	if(pipe(fd1)==-1){
		perror("Pipe Creation Failed \n");
		exit(0);
	}
	if(pipe(fd2)==-1){
		perror("Pipe Creation Failed \n");
		exit(0);
	}
	pid=fork();
	if(pid>0){
		close(fd1[0]);
		close(fd2[1]);
		while(1){
			memset(message,0,sizeof(message));
			printf("Write data for child: ");
			gets(message);
			write(fd1[1],message,1024);
			if(strcmp(message,"exit")==0) break;
			memset(buffer,0,sizeof(buffer));
			read(fd2[0],buffer,1024);
			printf("Recieved data from child: %s \n",buffer);
			if(strcmp(buffer,"exit")==0) break;
		}
	}
	else{
		close(fd1[1]);
		close(fd2[0]);
		while(1){
			memset(buffer,0,sizeof(buffer));
			read(fd1[0],buffer,1024);
			printf("Received data from parent: %s\n ",buffer);
			if(strcmp(buffer,"exit")==0) break;
			memset(message,0,sizeof(message));
			printf("Write data for parent:");
			gets(message);
			write(fd2[1],message,1024);
			if(strcmp(message,"exit")==0) break;
		}
	}
}
		
