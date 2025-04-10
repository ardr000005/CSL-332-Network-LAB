#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<netdb.h>
#include<time.h>
#include<sys/time.h>
#include<sys/types.h>

void func(int client_sock)
{
	int next=0,c,f,ack=-12;
	char buffer[100];
	memset(buffer,'\0',sizeof(buffer));
	while(1)
	{
		recv(client_sock,buffer,sizeof(buffer),0);
		if(strcmp(buffer,"EXIT")==0)
		{
			printf("Exiting \n");
			break;
		}
		
		f=atoi(buffer);
		
		if(f!=next)
		{
			printf("Discarding Frame %d \n",f);
			memset(buffer,'\0',sizeof(buffer));
			snprintf(buffer,sizeof(buffer),"%d",ack);
			send(client_sock,buffer,sizeof(buffer),0);
		}
		else
		{
		
		c=rand()%3;
		
		switch(c)
		{
			case 0 : printf("Acknowledgemnet send failed\n");
				 break;
			
			case 1 : ack=f;
				 printf("Frame received %d \n",ack);
				 printf("Sending acknowledgement %d \n",ack);
				 memset(buffer,'\0',sizeof(buffer));
				 snprintf(buffer,sizeof(buffer),"%d",ack);
				 send(client_sock,buffer,sizeof(buffer),0);
				 next=ack+1;
				 break;
				 
			case 2 : ack=f;
				 printf("Frame received %d \n",ack);
				 printf("Sending acknowledgement %d \n",ack);
				 memset(buffer,'\0',sizeof(buffer));
				 snprintf(buffer,sizeof(buffer),"%d",ack);
				 send(client_sock,buffer,sizeof(buffer),0);
				 next=ack+1;
				 break;
		}
		}
	}
}

int main(void)
{
	int sock_desc,client_sock,client_size;
	struct sockaddr_in server_addr,client_addr;
	
	sock_desc=socket(AF_INET,SOCK_STREAM,0);
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2000);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	if(bind(sock_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("Error Binding \n");
	}
	printf("Binded to port\n");
	
	if(listen(sock_desc,1)<0)
	{
		printf("Error Listening \n");
	}
	printf("Listening......\n");
	
	client_size=sizeof(client_addr);
	client_sock=accept(sock_desc,(struct sockaddr*)&client_addr,&client_size);
	if(client_sock<0)
	{
		printf("Error connecting to client\n");
	}
	
	func(client_sock);
	close(client_sock);
	close(sock_desc);
	return 0;
	
}
