#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

int main(void)
{
	int sock_desc,client_sock,client_size;
	struct sockaddr_in server_addr,client_addr;   
	char server_msg[1000],client_msg[1000];
	
	sock_desc=socket(AF_INET,SOCK_STREAM,0);
	
	if(sock_desc<0)
	{
		printf("Error creating socket \n");
		return -1;
	}
	
	server_addr.sin_family=AF_INET;                        
	server_addr.sin_port=htons(2000);                     
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");   
	
	if(bind(sock_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("Error Binding to port\n");
		return -1;
	}

	if(listen(sock_desc,1)<0)
	{
		printf("Error Listening\n");
	}
	
	printf("Listening ......\n");
	client_size=sizeof(client_addr);
	client_sock=accept(sock_desc,(struct sockaddr*)&client_addr,&client_size);
	
	if(client_sock<0)
	{
		printf("Error Accepting connections....\n");
		return -1;
	}
	
	memset(server_msg,'\0',sizeof(server_msg));
	memset(client_msg,'\0',sizeof(client_msg));
	
	if(recv(client_sock,client_msg,sizeof(client_msg),0)<0)  
	{
		printf("Error receiving \n");
		return -1;
	}
	
	printf("MESSAGE FROM CLIENT IS \t");
	printf("%s",client_msg);
	
	strcpy(server_msg,"HELLO FROM SERVER");
	
	if(send(client_sock,server_msg,sizeof(server_msg),0)<0) 
	{
		printf("Error sending \n");
		return -1;
	}
	
	close(client_sock);
	close(sock_desc);
	
	return 0;
	
	
	
	
}
