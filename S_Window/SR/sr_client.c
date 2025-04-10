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

struct timeval timeout;

void func(int sock_desc,int nf,int ws)
{
	int i,ack,f,c,count=0,w1=0,w2=ws-1;
	char buffer[100];
	memset(buffer,'\0',sizeof(buffer));
	
	if(setsockopt(sock_desc,SOL_SOCKET,SO_RCVTIMEO,(const char*)&timeout,sizeof(timeout))<0)
	perror("setsockopt(SO_RCVTIMEO)failed");
	
	for(i=0;i<nf && i<ws;i++)
	{
		printf("Sending Frames %d\n",i);
		memset(buffer,'\0',sizeof(buffer));
		snprintf(buffer,sizeof(buffer),"%d",i);
		send(sock_desc,buffer,sizeof(buffer),0);
	}
	while(1)
	{
		if(count==nf)
		{
			printf("Exiting ......\n");
			memset(buffer,'\0',sizeof(buffer));
			strcpy(buffer,"EXIT");
			send(sock_desc,buffer,sizeof(buffer),0);
			break;
		}
		if(i<nf && w2-w1 != ws-1 )
		{
			printf("Sending Frames %d\n",i);
			memset(buffer,'\0',sizeof(buffer));
			snprintf(buffer,sizeof(buffer),"%d",i);
			send(sock_desc,buffer,sizeof(buffer),0);
			i++;
			w2++;
		}
		f=recv(sock_desc,buffer,sizeof(buffer),0);
		ack=atoi(buffer);
		if(f>0)
		{
			if(ack==-1)
			{
				printf("Negative acknowledgement received for frame %d\n",w1);
				printf("Resending frame %d\n",w1);
				memset(buffer,'\0',sizeof(buffer));
				snprintf(buffer,sizeof(buffer),"%d",w1);
				send(sock_desc,buffer,sizeof(buffer),0);
			}
			else
			{
				printf("Acknowledgment received for %d\n",ack);
				w1++;
				count++;
			}
		}
	}
	
}

int main(void)
{
	int sock_desc,nf,ws;
	struct sockaddr_in server_addr,client_addr;
	
	sock_desc=socket(AF_INET,SOCK_STREAM,0);
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2000);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	timeout.tv_sec=3;
	timeout.tv_usec=0;
	
	connect(sock_desc,(struct sockaddr*)&server_addr,sizeof(server_addr));
	
	printf("Enter the total number of frames \n");
	scanf("%d",&nf);
	
	printf("Enter the window size \n");
	scanf("%d",&ws);
	
	func(sock_desc,nf,ws);
	close(sock_desc);
	
	return 0;
		
}
