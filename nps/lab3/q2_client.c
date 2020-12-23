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
	int sa;
	socklen_t len;
	printf("INPUT port number:");
	scanf("%d",&x);
	struct sockaddr_in server,client;
	char buff[max_lim];
	
	//2. create socket
	s=socket(AF_INET,SOCK_DGRAM,0);
	if(s==-1){printf("\nSocket creation error.");exit(0);}
	printf("\nSocket created.");
	
	//3. assign values to server
	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	sa=sizeof(server);
	len=sizeof(server);
	
	//4. inside loop,send msg to server
	while(1){
		//send
		printf("\n\nEnter string: \n");
		int c;while((c = getchar()) != '\n' && c != EOF);
		scanf("%[^\n]%*c",buff);
		sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&server,len);
		if(sntb==-1){printf("\nMessage sending Failed");close(s); exit(0);}
		if(!strcmp(buff,"stop")) break;
	}
	close(s);
}

