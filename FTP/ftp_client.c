#include<stdlib.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>

int main(void)
{
	FILE *fp1;
	int sock_desc,s;
	struct sockaddr_in server_addr;
	char rcvg[100],file[100],name[10];
	
	sock_desc=socket(AF_INET,SOCK_STREAM,0);
	
	if(sock_desc<0)
	{
		printf("Error creating socket\n");
	}
	
	memset(name,'\0',sizeof(name));
	memset(file,'\0',sizeof(file));
	memset(rcvg,'\0',sizeof(rcvg));
	
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(2000);
	server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	printf("Enter the file name\n");
	scanf("%s",name);
	printf("Enter the file to write output\n");
	scanf("%s",file);
	
	fp1=fopen(file,"w");
	
	if(connect(sock_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
	{
		printf("Error connecting \n");
	}
	
	send(sock_desc,name,sizeof(name),0);
	printf("------------------------------\n");
	
	while(1)
	{
		s=recv(sock_desc,rcvg,sizeof(rcvg),0);
		rcvg[s]='\0';
		if(strcmp(rcvg,"ERROR")==0)
		{
			printf("Error sending file \n");
			exit(1);
			fclose(fp1);
			close(sock_desc);
		}
		else if(strcmp(rcvg,"COMPLETED")==0)
		{
			printf("------------------------------\n");
			printf("File Transferred sucessfully");
			fclose(fp1);
			break;
		}
		else
		{
			fprintf(fp1,"%s",rcvg);
			printf("%s",rcvg);
		}
	}
	
	close(sock_desc);
	
	return 0;
}
