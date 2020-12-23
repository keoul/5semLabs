#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>
int main()
{
int s,r,recb,sntb,x;
printf("INPUT port number: "); //port number for communication
scanf("%d", &x);
struct sockaddr_in server;
char buff[50];
s=socket(AF_INET,SOCK_STREAM,0); //socket creation
if(s==-1)
{
printf("\nSocket creation error.");
exit(0);
}
printf("\nSocket created.");
server.sin_family=AF_INET;
server.sin_port=htons(x);
server.sin_addr.s_addr=inet_addr("127.0.0.1");
r=connect(s,(struct sockaddr*)&server,sizeof(server)); //socket connecting
if(r==-1)
{
printf("\nConnection error.");
exit(0);
}
printf("\nSocket connected.\n");

printf("\n\n");
strcpy(buff,"");
printf("Enter alphanumeric string: ");
scanf("%s", buff);
sntb=send(s,buff,sizeof(buff),0); //sending data to server
if(sntb==-1)
{
close(s);
printf("\nMessage sending failed.");
exit(0);
}
close(s);
}