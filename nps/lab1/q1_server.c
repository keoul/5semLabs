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
	int s,r,recb,sntb,x,ns,a=0;
	printf("INPUT port number:");
	scanf("%d",&x);
	socklen_t len;
	struct sockaddr_in server,client;
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
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	server.sin_port=htons(x);
	
	//4. bind address to socket
	r=bind(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1){
		printf("\nBinding error.");
		exit(0);
	}
	printf("\nSocket binded.");
	
	//5. make socket passive(announce willingness to accept connection) 
	r=listen(s,1);
	if(r==-1){
		close(s); exit(0);
	}
	printf("\nSocket listening.");
	len=sizeof(client);
	
	//6. block until connection request arrives from client
	ns=accept(s,(struct sockaddr*)&client,&len);
	if(ns==-1){
		close(s); exit(0);
	}
	printf("\nSocket accepting.");


	recb=recv(ns,buff,sizeof(buff),0);
	if(recb==-1){printf("\nMsg Recieve Failed");close(s); close(ns); exit(0);}
	printf("\n\nArray size:%s\n",buff);

	int n=atoi(buff),arr[n],choice;
	for(int i=0;i<n;i++){
		recb=recv(ns,buff,sizeof(buff),0);
		if(recb==-1){printf("\nMsg Recieve Failed");close(s); close(ns); exit(0);}
		arr[i]=atoi(buff);
	}
	printf("Entered array is: ");
	for(int i=0;i<n;i++) printf("%d ",arr[i]);
	int key,i,j,temp,flag;
	char oa[max_lim],ea[max_lim];
	strcpy(oa,"Odd elements are:");
	strcpy(ea,"Even elements are:");
	
	while(1){
		recb=recv(ns,buff,sizeof(buff),0);
		if(recb==-1){printf("\nMsg Recieve Failed");close(s); close(ns); exit(0);}
		printf("\n\nClient chose:%s\n",buff);
		if(!strcmp(buff,"exit")) break;
		
		choice=atoi(buff);
		switch(choice){
			case 1:
				recb=recv(ns,buff,sizeof(buff),0);
				if(recb==-1){printf("\nMsg Recieve Failed");close(s); close(ns); exit(0);}
				printf("Client searching for %s.",buff);
				key=atoi(buff);
				flag=-1;
				for(i=0;i<n;i++) if(key==arr[i]){flag=i;break;}
				if(flag==-1){strcpy(buff,"Element not found.");}
				else{strcpy(buff,"Element found.");}
				printf("\n%s",buff);
				sntb=send(ns,buff,sizeof(buff),0);
				if(sntb==-1){printf("Msg Send Failed");close(s);close(ns);exit(0);}
				break;
			case 2:
				recb=recv(ns,buff,sizeof(buff),0);
				if(recb==-1){printf("\nMsg Recieve Failed");close(s); close(ns); exit(0);}
				if(!strcmp(buff,"a")){
					for(i=0;i<n-1;i++){
						for(j=0;j<n-i-1;j++)
						  if(arr[j]>arr[j+1]){temp=arr[j];arr[j]=arr[j+1];arr[j+1]=temp;}
					}
					strcpy(buff,"Sorted array is: ");
					for(i=0;i<n;i++) sprintf(buff,"%s %d",buff,arr[i]);
				}
				else if(!strcmp(buff,"d")){
					for(i=0;i<n-1;i++){
						for(j=0;j<n-i-1;j++)
						  if(arr[j]<arr[j+1]){temp=arr[j];arr[j]=arr[j+1];arr[j+1]=temp;}
					}
					strcpy(buff,"Sorted array is: ");
					for(i=0;i<n;i++) sprintf(buff,"%s %d",buff,arr[i]);
					
				}
				else{strcpy(buff,"Wrong choice.");}
				printf("\n%s.",buff);
				sntb=send(ns,buff,sizeof(buff),0);
				if(sntb==-1){printf("Msg Send Failed");close(s);close(ns);exit(0);}
				break;
			case 3:
				for(i=0;i<n-1;i++){
					for(j=0;j<n-i-1;j++)
					  if(arr[j]>arr[j+1]){temp=arr[j];arr[j]=arr[j+1];arr[j+1]=temp;}
				}
				for(i=0;i<n;i++){
					if(arr[i]%2==0) sprintf(ea,"%s %d",ea,arr[i]);
					else sprintf(oa,"%s %d",oa,arr[i]);
				}
				sprintf(buff,"%s\n%s",oa,ea);
				printf("%s",buff);
				sntb=send(ns,buff,sizeof(buff),0);
				if(sntb==-1){printf("Msg Send Failed");close(s);close(ns);exit(0);}
				break;
			default:strcpy(buff,"Wrong choice.");
		}
	}
	
	printf("\n");
	close(ns); close(s);
}




