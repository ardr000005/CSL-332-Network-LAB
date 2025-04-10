#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

int main(void)
{
	int sock_desc,sc_length;
	struct sockaddr_in server_addr,client_addr;
	char client_msg[1000],server_msg[1000];
	
	sock_desc=socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	
	if(sock_desc<0)
	{
		printf("Error Creating socket\n");
	}
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2000);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	memset(server_msg,'\0',sizeof(server_msg));
	memset(client_msg,'\0',sizeof(client_msg));
	
	sc_length=sizeof(server_addr);
	strcpy(client_msg,"Hello FROM CLIENT");
	if(sendto(sock_desc,client_msg,sizeof(client_msg),0,(struct sockaddr*)&server_addr,sc_length)<0) 
	{
		printf("Error sending \n");
		return -1;
	}
	
	if(recvfrom(sock_desc,server_msg,sizeof(server_msg),0,(struct sockaddr*)&server_addr,&sc_length)<0) 
	{
		printf("Error receiving \n");
		return -1;
	}
	printf("%s",server_msg);
	close(sock_desc);
}
