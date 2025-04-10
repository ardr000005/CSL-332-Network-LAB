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
	
	if(bind(sock_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("Error Binding Port\n");
		return -1;
	}
	
	if(listen(sock_desc,1)<0)
	{
		printf("Error Listening\n");
		return -1;
	}
	
	printf("Listening........................................\n");
	
	client_size=sizeof(client_addr);
	client_sock=accept(sock_desc,(struct sockaddr*)&client_addr,&client_size);
	
	if(client_sock<0)
	{
		printf("Error accepting connection\n");
		return -1;
	}
	
	while(k!=0)
	{
		memset(buffer,'\0',sizeof(buffer));
		y=recv(client_sock,buffer,sizeof(buffer),0);
		if(y==-1)
		{
			printf("Cant Recieve\n");
			exit(1);
		}
		if(strcmp(buffer,"FRAME")==0)
		{
			printf("Frame %d Received \n",m);
			printf("Sending acknowledgement for frame %d\n",m);
		}
		else
		{
			printf("Frame didnot received \n");
		}
		if(m%2==0)
		{
			memset(buffer,'\0',sizeof(buffer));
			strcpy(buffer,"ACK");
		}
		else
		{
			printf("Acknowledgement lost \n");
			for(p=0;p<3;p++)
			{
				printf("Waiting for %d seconds",p+1);
			}
			printf("Retransmitting....... \n");
			memset(buffer,'\0',sizeof(buffer));
			strcpy(buffer,"ACK");
			sleep(3);
			
		}
		
		z=send(client_sock,buffer,sizeof(buffer),0);
		if(z==-1)
		{
			printf("Error sending .\n");
			return -1;
		}
		m++;
		k--;
	}
	close(sock_desc);
	close(client_sock);
	
	return 0;
}
