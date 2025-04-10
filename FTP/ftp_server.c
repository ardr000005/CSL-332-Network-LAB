#include<stdlib.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>

int main(void)
{
	FILE *fp;
	int sock_desc,n,client_size,client_sock;
	struct sockaddr_in server_addr,client_addr;
	char rcvg[100],file_read[100];
	
	sock_desc=socket(AF_INET,SOCK_STREAM,0);
	
	if(sock_desc<0)
	{
		printf("Error creating socket\n");
	}
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2000); 
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	if(bind(sock_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("Error Binding to socket\n");
	}
	
	if(listen(sock_desc,1)<0)
	{
		printf("Error Listening \n");
	}
	printf("Listening .......\n");
	
	client_size=sizeof(client_addr);
	client_sock=accept(sock_desc,(struct sockaddr*)&client_addr,&client_size);
	
	
	memset(rcvg,'\0',sizeof(rcvg));
	memset(file_read,'\0',sizeof(file_read));
	
	n=recv(client_sock,rcvg,sizeof(rcvg),0);
	rcvg[n]='\0';
	
	fp=fopen(rcvg,"r");
	if(fp==NULL)
	{
		printf("Error opening file or file doesnot exists\n");
		memset(rcvg,'\0',sizeof(rcvg));
		strcpy(rcvg,"ERROR");
		send(client_sock,rcvg,sizeof(rcvg),0);
		close(client_sock);
		close(sock_desc);
	}
	else
	{
		while(fgets(file_read,sizeof(file_read),fp))
		{
			send(client_sock,file_read,sizeof(file_read),0);
		}
		if(!fgets(file_read,sizeof(file_read),fp))
		{
			printf("DONE\n");
			memset(rcvg,'\0',sizeof(rcvg));
			strcpy(rcvg,"COMPLETED");
			send(client_sock,rcvg,sizeof(rcvg),0);
		}
		fclose(fp);
	}
	
	close(client_sock);
	close(sock_desc);
	
}
