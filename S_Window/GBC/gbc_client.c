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

struct timeval timeout; 

void func(int sock_desc,int nf, int ws)
{
	int w1=0,w2=ws-1,i,flag=0,ack,n,j;
	char buffer[100];
	
	memset(buffer,'\0',sizeof(buffer));
	
	if(setsockopt(sock_desc,SOL_SOCKET,SO_RCVTIMEO,(const char*)&timeout,sizeof(timeout))<0) 
	{
		perror("setsockopt(SO_RCVTIMEO) failed"); 
	}
	
	for(i=0;i<nf && i<ws;i++)
	{
		memset(buffer,'\0',sizeof(buffer));
		printf("Sending Frame %d\n",i);
		snprintf(buffer,sizeof(buffer),"%d",i);
		send(sock_desc,buffer,sizeof(buffer),0);
	}
	while(1)
	{
		if(w2-w1!=ws-1 && flag==0 && i<nf)
		{
			memset(buffer,'\0',sizeof(buffer));
			printf("Sending Frame %d\n",i);
			snprintf(buffer,sizeof(buffer),"%d",i);
			send(sock_desc,buffer,sizeof(buffer),0);
			i++;
			w2++;
		}
		flag=0;
		memset(buffer,'\0',sizeof(buffer));
		n=recv(sock_desc,buffer,sizeof(buffer),0);
		ack=atoi(buffer);
		if(n>0)
		{
			if(ack+1==nf)
			{
				printf("Received Acknowledgement %d \n EXITING..... \n",ack);
				memset(buffer,'\0',sizeof(buffer));
				strcpy(buffer,"EXIT");
				send(sock_desc,buffer,sizeof(buffer),0);
				break;
			}
			else if(ack==w1)
			{
				w1++;
				printf("Received Acknowledgement %d \n",ack);
			}
			else
			{
				printf("Resending Frames .....\n");
				for(j=w1;j<w1+ws && j<nf;j++)
				{
					printf("Sending Frame %d\n ",j);
					memset(buffer,'\0',sizeof(buffer));
					snprintf(buffer,sizeof(buffer),"%d",j);
					send(sock_desc,buffer,sizeof(buffer),0);
				}
				flag=1;
			}
		}
		
	}
		
}

int main(void)
{
	int sock_desc,nf,w,server_size;
	struct sockaddr_in server_addr,client_addr;
	
	sock_desc=socket(AF_INET,SOCK_STREAM,0);
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2000);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	timeout.tv_sec=3;  
	timeout.tv_usec=0; 
	server_size=sizeof(server_addr);
	if(connect(sock_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("Error accepting connection from server\n");
	}
	
	printf("Enter the number of frames to be send\n");
	scanf("%d",&nf);
	
	printf("Enter the window size\n");
	scanf("%d",&w);
	
	func(sock_desc,nf,w);
	close(sock_desc);
	return 0;
	
}


