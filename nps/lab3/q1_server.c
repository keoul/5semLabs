#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
int main()
{
int s,r,recb,sntb,x,ns,a=0;
printf("INPUT port number: "); //port number for communication
scanf("%d", &x);
socklen_t len;
struct sockaddr_in server,client;
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
server.sin_addr.s_addr=htonl(INADDR_ANY);
r=bind(s,(struct sockaddr*)&server,sizeof(server)); //socket binding
if(r==-1)
{
printf("\nBinding error.");
exit(0);
}
printf("\nSocket binded.");
r=listen(s,1);
if(r==-1)
{
close(s);
exit(0);
}
printf("\nSocket listening.");
len=sizeof(client);
ns=accept(s,(struct sockaddr*)&client, &len); //socket accepting
if(ns==-1)
{
close(s);
exit(0);
}
printf("\nSocket accepting.\n");
int pid=fork();
while(1){
if(pid>0){
//parent process

printf("\nParent's PID: %d",pid);
printf("\n\nParent-Type message:\n");
scanf("%s", buff2);
sntb=send(ns,buff2,sizeof(buff2),0); //sending data to client
if(sntb==-1)
{
printf("\nMessage sending failed.");
close(s);
close(ns);
exit(0);
}
if(strcmp(buff2,"BYE")==0)
break;
}
else{
//child process
printf("\nChild's PID: %d",pid);
recb=recv(ns,buff,sizeof(buff),0); //receiving data from client
if(recb==-1)
{
printf("\nMessage receiving failed.");
close(s);
close(ns);
exit(0);
}
if(strcmp(buff,"BYE")==0)
break;
printf("\nMessage received by child: ");
printf("%s\n", buff);
}
}
close(ns);
close(s);
}