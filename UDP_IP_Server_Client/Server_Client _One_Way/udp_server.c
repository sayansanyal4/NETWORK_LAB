//Write a code to implement one way multiple time communication b/w server and client machine by using UDP/IP SOCKET


#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#define PORT 8080
void main()
{
        char buffer[1024];
	int svrsock_fd;
	struct sockaddr_in svraddr,clnaddr;
	socklen_t svraddrlen=sizeof(struct sockaddr_in);
	socklen_t clnaddrlen=sizeof(struct sockaddr_in);
	svrsock_fd=socket(AF_INET,SOCK_DGRAM,0);
	svraddr.sin_family=AF_INET;
	svraddr.sin_addr.s_addr=INADDR_ANY;
	svraddr.sin_port=htons(PORT);
	bind(svrsock_fd,(struct sockaddr *)&svraddr,svraddrlen);
	printf("WAITING FOR UDP/IP CLIENT REQUEST\n");
	while(1)
	{
		memset(buffer,0,sizeof(buffer));
		recvfrom(svrsock_fd,buffer,sizeof(buffer),0,&clnaddr,&clnaddrlen);
		printf("Received data from UDP/IP client:%s\n",buffer);
		if(strcmp(buffer,"exit")==0)break;
		
		
	}
}
