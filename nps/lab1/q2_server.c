//1. include header files
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>

#define max_lim 100
int main(){
	int s,r,recb,sntb,x;
	int ca;
	printf("INPUT port number:");
	scanf("%d",&x);
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[max_lim],str[max_lim];
	
	//2. create socket
	s=socket(AF_INET,SOCK_DGRAM,0);
	if(s==-1){printf("\nSocket creation error.");exit(0);}
	printf("\nSocket created.");
	
	//3. assign values to server
	server.sin_family=AF_INET;
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	server.sin_port=htons(x);
	len=sizeof(client);
	ca=sizeof(client);
	
	//4. bind address to socket
	r=bind(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1){printf("\nBinding error.");exit(0);}
	printf("\nSocket binded.");
	int l,h,n;

	//5. inside loop,recive msg from client
	while(1){
	
		//recieve
		recb=recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca);
		if(recb==-1){printf("\nMessage Recieving Failed");close(s); exit(0);}
		printf("\n\nRecieved string from client: %s",buff);
		if(!strcmp(buff,"halt")) break;

		strcpy(str,buff);
		l=0;
		h=strlen(str)-1;
		sprintf(buff,"\"%s\" is Palindrome.",str);
		while(h>l){ 
		    if(str[l++]!=str[h--]){sprintf(buff,"\"%s\" is Not Palindrome.",str);break;}
		}
		h=strlen(str);
		sprintf(buff,"%s Length of string is %d and",buff,h);
		
		n=0;
		for(int i=0;i<h;i++)
			if(str[i]=='a'||str[i]=='e'||str[i]=='o'||str[i]=='i'||str[i]=='u') n++;
			
		sprintf(buff,"%s it contains %d vowels.",buff,n);		

		//send
		sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&client,len);
		if(sntb==-1){printf("\nMessage Sending Failed");close(s); exit(0);}
		if(!strcmp(buff,"halt")) break;
	}
	close(s);
}
