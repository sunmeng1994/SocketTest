#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<ctype.h>
#include<arpa/inet.h>
#include<netinet/in.h>
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
    else
    {
	printf("create serverSocket success:%d\n",serverSocket);
    }
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family=AF_INET;
    //监听本地所有地址
    server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    server_addr.sin_port=htons(6666); //端口号
    if(bind(serverSocket,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
	printf("fuck bind fail\n");
    }
    else
    {
	printf("bind success!\n");
    }

    if(listen(serverSocket,10)<0)
    {
	printf("fucking listen failed\n");
	return 0;
    }
    else
    {
	printf("listen success\n");
    }
    printf("等待客户端的连接i\n");
    int done=1;
    while(done)
    {
	struct sockaddr_in client;
	int client_sock;	
	char client_ip[64];
	char buf[256];
	socklen_t client_addr_len;
	client_addr_len=sizeof(client);
	client_sock=accept(serverSocket,(struct sockaddr*)&client,&client_addr_len);
	//目标客户端ip和port
	printf("client ip:%s\t,port:%d\n",
	      inet_ntop(AF_INET,&client.sin_addr.s_addr,client_ip,sizeof(client_ip))
	      ,ntohs(client.sin_port));
	int len=read(client_sock,buf,sizeof(buf)-1);
	buf[len]='\0';
	printf("recieve[%d]:%s\n",len,buf);
	len =write(client_sock,buf,len);
	close(client_sock);
    }
    return 0;
}
