#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<ctype.h>
#include<arpa/inet.h>
#define SERVER_PORT 7777
int main()
{
    int serverSocket;
    struct sockaddr_in server_addr;
    //创建
    serverSocket=socket(AF_INET,SOCK_STREAM,0);
    if(serverSocket<0)
    {
	printf("socket fucking failed\n");
    } 
    //bzero(&server_addr,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    //监听本地所有地址
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htonl(SERVER_PORT); //端口号
    if(bind(serverSocket,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
	printf("fuck bind fail\n");
    }
    if(listen(serverSocket,10)<0)
    {
	printf("fucking listen failed\n");
    }
    printf("等待客户端的连接i\0");
    int done=1;
    while(done)
    {
	struct sockaddr_in client;
	int client_sock;	
	char client_ip[64];
	socklen_t client_addr_len;
	client_addr_len=sizeof(client);
	client_sock=accept(serverSocket,(struct sockaddr*)&client,&client_addr_len);
	printf("client ip:%s\t,port:%d\n",
	      inet_ntop(AF_INET,&client.sin_addr.s_addr,client_ip,sizeof(client_ip))
	      ,ntohs(client.sin_port));
    }
    return 0;
}
