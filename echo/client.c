//
//  main.c
//  socketclient
//
//  Created by dogrest on 2019/3/31.
//  Copyright © 2019 dogrest. All rights reserved.
//
#include<unistd.h>
#include<sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    int sockfd;
    char* message="gofuck";
    struct sockaddr_in servaddr;
    
    sockfd=socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd<0)
    {
	printf("create socket error\n");
    }
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    if(inet_pton(AF_INET,"165.85.49.169",&servaddr.sin_addr)<=0)
    {
	printf("inet_pton error\n");
    }
    servaddr.sin_port=htons(6666);
    if(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))<0)
    {
	printf("connect error\n");
	return 0;
    }
    
    write(sockfd,message,strlen(message));
    printf("write success!\n");
    char buf[64];
    memset(buf, 0, sizeof(buf));
    int n=read(sockfd,buf,sizeof(buf)-1);
    if(n>0)
    {
        buf[n]='\0';
        printf("receive:%s\n",buf);
    }
    else
    {
        printf("read error\n");
    }
    printf("finished.\n");
    close(sockfd);
    return 0;
}
