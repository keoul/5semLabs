//1. include header files
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/stat.h>

#define max_lim 100

int main(){
	int s,r,recb,sntb,x;
	printf("INPUT port number:");
	scanf("%d",&x);
	struct sockaddr_in server;
	char buff[max_lim];

	//2. create socket
	s=socket(AF_INET,SOCK_STREAM,0);
	if(s==-1){
		printf("\nSocket creation error.");
		exit(0);
	}
	printf("\nSocket created.");

	//3. initialize server
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	server.sin_port=htons(x);
	
	//4. connect to server
	r=connect(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1){
		printf("\nConnection error.");
		exit(0);
	}
	printf("\nSocket connected.");
	
	printf("\n\nEnter size of array:");
	scanf("%s",buff);
	sntb=send(s,buff,sizeof(buff),0);
	if(sntb==-1){printf("\nMsg Send Failed");close(s); exit(0);}

	int n=atoi(buff);
	printf("Enter %s numbers:",buff);
	for(int i=0;i<n;i++){
		scanf("%s",buff);
		sntb=send(s,buff,sizeof(buff),0);
		if(sntb==-1){printf("\nMsg Send Failed");close(s); exit(0);}
	}
	printf("\nEnter 1:search 2:sort 3:split\nEnter \"exit\" to exit.");
	int key,choice;
	
	while(1){
		printf("\n\nEnter choice:");
		scanf("%s",buff);
		sntb=send(s,buff,sizeof(buff),0);
		if(sntb==-1){printf("\nMsg Send Failed");close(s); exit(0);}
		if(!strcmp(buff,"exit")) break;
		
		choice=atoi(buff);
		switch(choice){
			case 1:
				printf("Enter search element:");
				scanf("%s",buff);
				sntb=send(s,buff,sizeof(buff),0);
				if(sntb==-1){printf("\nMsg Send Failed");close(s); exit(0);}
				recb=recv(s,buff,sizeof(buff),0);
				if(recb==-1){printf("Reply Recieve Failed");close(s); exit(0);}
				printf("%s",buff);
				break;
			case 2:
				printf("Enter a:ascending or d:descending\n");
				scanf("%s",buff);
				sntb=send(s,buff,sizeof(buff),0);
				if(sntb==-1){printf("\nMsg Send Failed");close(s); exit(0);}
				recb=recv(s,buff,sizeof(buff),0);
				if(recb==-1){printf("Reply Recieve Failed");close(s); exit(0);}
				printf("%s",buff);
				break;
			case 3:
				recb=recv(s,buff,sizeof(buff),0);
				if(recb==-1){printf("Reply Recieve Failed");close(s); exit(0);}
				printf("%s",buff);
				break;
			default:strcpy(buff,"Wrong choice.");
		}
	}
	printf("\n\n");
	close(s);
}
