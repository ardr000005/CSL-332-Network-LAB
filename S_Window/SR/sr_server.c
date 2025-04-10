#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/time.h>
#include<time.h>
#include<netdb.h>
#include<sys/types.h>

void func(int client_sock)
{
	int ack,f,c,next=0;
	char buffer[100];
	memset(buffer,'\0',sizeof(buffer));
	while(1)
	{
		memset(buffer,'\0',sizeof(buffer));
		recv(client_sock,buffer,sizeof(buffer),0);
		if(strcmp(buffer,"EXIT")==0)
		{
			printf("Exiting....");
			break;
		}
		f=atoi(buffer);
		c=rand()%3;
		switch(c)
		{
			case 0: printf("Frame %d didnot Received\n",next);
				printf("Sending negative acknowledgement for frame %d\n",next);
				memset(buffer,'\0',sizeof(buffer));
				ack=-1;
				snprintf(buffer,sizeof(buffer),"%d",ack);
				send(client_sock,buffer,sizeof(buffer),0);
				break;
				
			case 1: ack=f;
				printf("Frame %d received \n",ack);
				printf("Sending acknowledgement for frame %d\n",ack);
				memset(buffer,'\0',sizeof(buffer));
				snprintf(buffer,sizeof(buffer),"%d",ack);
				send(client_sock,buffer,sizeof(buffer),0);
				next=ack+1;
				break;
			
			case 2: ack=f;
				printf("Frame %d received \n",ack);
				printf("Sending acknowledgement for frame %d\n",ack);
				memset(buffer,'\0',sizeof(buffer));
				snprintf(buffer,sizeof(buffer),"%d",ack);
				send(client_sock,buffer,sizeof(buffer),0);
				next=ack+1;
				break;
		}
	}
}

int main(void)
{
	int sock_desc,client_size,client_sock;
	struct sockaddr_in server_addr,client_addr;
	
	sock_desc=socket(AF_INET,SOCK_STREAM,0);
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2000);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	bind(sock_desc,(struct sockaddr*)&server_addr,sizeof(server_addr));
	
	listen(sock_desc,1);
	printf("Listening.......................\n");
	
	client_size=sizeof(client_addr);
	client_sock=accept(sock_desc,(struct sockaddr*)&client_addr,&client_size);
	
	func(client_sock);
	close(client_sock);
	close(sock_desc);
	
	return 0;
		
}
