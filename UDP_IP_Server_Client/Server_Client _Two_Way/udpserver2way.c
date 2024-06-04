#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#define PORT 8080
void main()
{char buffer[1024],message[1024];
int svrsock_fd;
struct sockaddr_in svraddr,clnaddr;
socklen_t svraddrlen=sizeof(struct sockaddr_in);
socklen_t clnaddrlen=sizeof(struct sockaddr_in);
svrsock_fd=socket(AF_INET,SOCK_DGRAM,0);
svraddr.sin_family=AF_INET;
svraddr.sin_addr.s_addr=INADDR_ANY;
svraddr.sin_port=htons(PORT);
bind(svrsock_fd,(struct sockaddr *)&svraddr,svraddrlen);
printf("WAITING FOR UDP/IP CLIENT\n");
while(1)
{
memset(buffer,0,sizeof(buffer));
recvfrom(svrsock_fd,buffer,sizeof(buffer),0,&clnaddr,&clnaddrlen);
printf("received data from UDP/IP CLIENT:%s\n",buffer);
if(strcmp(buffer,"exit")==0)break;
memset(message,0,sizeof(message));
printf("enter data for UDP/IP server:");
gets(message);
sendto(svrsock_fd,message,sizeof(message),0,&clnaddr,clnaddrlen);
if(strcmp(message,"exit")==0)break;
}
}

