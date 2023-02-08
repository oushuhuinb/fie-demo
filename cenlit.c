#include <stdio.h>
#include <sys/types.h>        
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <event2/listener.h>
#include <event.h>


int main()
{
    int sockfd=socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in saddr;
    memset(&saddr,0,sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8000);//htons主机转网络字节号 防止大小端
    saddr.sin_addr.s_addr = inet_addr("10.0.3.15");
 
    // int res = connect(sockfd,(struct sockaddr*)&saddr,sizeof(saddr));//进行三次握手
    // if(res == -1)
    // {
    //     perror("connect");
    //     exit(1);
    // }
    char buf[32]={0};
    struct event_base* base=event_base_new();

    struct bufferevent* bev=bufferevent_socket_new(base,sockfd,BEV_OPT_CLOSE_ON_FREE);

    bufferevent_socket_connect(
        bev,
        (struct sockaddr*)&saddr,
        sizeof(saddr)
    );
    

    while(1)
    {

        scanf("%s",buf);
        send(sockfd,buf,strlen(buf),0);
    }  
    printf("11111\n");
}