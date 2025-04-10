#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>

int main(void)
{
	int sock_desc,client_sock,client_size,y,k=5,m=0,p,z;
	struct sockaddr_in server_addr,client_addr;
	char buffer[100];
	memset(buffer,'\0',sizeof(buffer));
	
	if((sock_desc=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		printf("Error Creating socket\n");
		return -1;
	}
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2000);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	if(connect(sock_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("Error Connecting to receiver\n");
	}
	printf("Connected to receiver\n");
	
	while(k!=0)
	{
		memset(buffer,'\0',sizeof(buffer));
		printf("Sending Frame %d\n",m);
		if(m%2==0)
		{
			memset(buffer,'\0',sizeof(buffer));
			strcpy(buffer,"FRAME");
		}
		else
		{
			printf("Frame lost \n");
			for(p=0;p<3;p++)
			{
				printf("Waiting for %d seconds",p+1);
			}
			printf("Retransmitting....... \n");
			memset(buffer,'\0',sizeof(buffer));
			strcpy(buffer,"FRAME");
			sleep(3);
		}
		
		z=send(sock_desc,buffer,sizeof(buffer),0);
		if(z==-1)
		{
			printf("Error sending .\n");
			return -1;
		}
		
		y=recv(sock_desc,buffer,sizeof(buffer),0);
		if(y==-1)
		{
			printf("Cant Recieve\n");
			exit(1);
		}
		
		if(strcmp(buffer,"ACK")==0)
		{
			printf("ACKNOWLEDGEMENT %d Received \n",m);
		}
		else
		{
			printf("ACKNOWLEDGEMENT didnot received \n");
		}
		
		
		m++;
		k--;
	}
	close(sock_desc);
	
	return 0;
}
