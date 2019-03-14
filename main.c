#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

#define MAXLINE 4096

int main()
{
    int listenfd,connfd;
    struct sockaddr_in servaddr;
    char buff[4096];
    int n;
    listenfd=socket(AF_INET,SOCK_STREAM,0);
    if(listenfd==-1)
    {
	printf("create socket error:");
	exit(0);
    }
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
    servaddr.sin_port=htons(6666);

    if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))==-1)
    {
	printf("bind sock erro");
	exit(0);
    }
    
    if(listen(listenfd,10)==-1)
    {
	printf("listen socket error:");
	exit(0);
    }
    printf("waiting for client `s request====\n");

    while(1)
    {
	connfd=accept(listenfd,(struct sockaddr*)NULL,NULL);
	if(connfd==-1)
	{
	    printf("accept socket error:");
	}
	else
	{
	    printf("fucking connect success!\n");
	    n=recv(connfd,buff,MAXLINE,0);
	    buff[n]='\0';
	    printf("recv msg from client :%S\n",buff);
	    close(connfd);
	}
    }
    close(listenfd);
}
