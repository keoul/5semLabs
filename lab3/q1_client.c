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
char buff[50],buff2[50];
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
printf("\nSocket connected.");
printf("\n\n");
int pid;
pid=fork();
while(1){
if(pid>0)
{
//parent process
printf("\nParent's PID: %d",pid);
recb=recv(s,buff,sizeof(buff),0); //receiving data from server
if(recb==-1)
{
printf("\nMessage receiving failed.");
close(s);
exit(0);
}
if(strcmp(buff,"BYE")==0)
break;
printf("\nMessage received by parent: ");
printf("%s\n", buff);
}
else
{
//child process
printf("\nChild's PID: %d",pid);
printf("\nChild-Type Message:\n");
scanf("%s", buff2);
sntb=send(s,buff2,sizeof(buff2),0); //sending data to server
if(sntb==-1)
{
close(s);
printf("\nMessage sending failed");
exit(0);
}
if(strcmp(buff2,"BYE")==0)
break;
}
}
close(s);
}