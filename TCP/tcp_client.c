#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(void)
{
	int sock_desc;
	struct sockaddr_in server_addr,client_addr;
	char server_msg[1000],client_msg[1000];
	
	sock_desc=socket(AF_INET,SOCK_STREAM,0);
	
	if(sock_desc<0)
	{
		printf("Error Creating Socket \n");
		return -1;
	}
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2000);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	if(connect(sock_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("Error connecting socket\n");
		return -1;
	}
	
	memset(server_msg,'\0',sizeof(server_msg));
	memset(client_msg,'\0',sizeof(client_msg));
	
	strcpy(client_msg,"HELLO FROM CLIENT");
	
	if(send(sock_desc,client_msg,sizeof(client_msg),0)<0) 
	{
		printf("Cant Send\n");
		return -1;
	}
	
	if(recv(sock_desc,server_msg,sizeof(server_msg),0)<0)   
	{
		printf("Received from server\n");
		return -1;
	}
	
	printf("message received\n");
	printf("%s",server_msg);
	
	close(sock_desc);
}
