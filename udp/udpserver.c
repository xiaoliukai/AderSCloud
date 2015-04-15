/*************************************************************************
    > File Name: server.c
    > Author: GatieMe
    > Mail: gatieme@163.com 
    > Created Time: 2015年04月11日 星期六 16时22分10秒
 ************************************************************************/

#include "udp.h"



/*  创建一个服务器  */
UdpServer* CreateUdpServer( )
{
    UdpServer *server = NULL;
   
    /*  首先开辟服务器的空间  */
    if((server = (UdpServer *)malloc(sizeof(UdpServer))) == NULL)
    {
        fprintf(stderr, "malloc server failed...\n'");
    }

    bzero(&server->m_serverAddr, sizeof(server->m_serverAddr));/*  全部置零  */  
    
    /* 设置地址相关的属性 */
    server->m_serverAddr.sin_family         =   AF_INET;  
    server->m_serverAddr.sin_addr.s_addr    =   htonl(INADDR_ANY);  
    server->m_serverAddr.sin_port           =   htons(UDP_SERVER_PORT);  
    
    /*  开始创建套接字  */
    /*  IPV4  SOCK_DGRAM 数据报套接字（UDP协议）  */
    server->m_socketFd                      =   socket(AF_INET, SOCK_DGRAM, 0);  
   
    /*  创套接字  */
    if(server->m_socketFd < 0)   
    {
        perror("socket create error\n");  
        exit(1);  
    }
    else
    {
        printf("UDP socket create success...\n");
        printf("创建套接字成功[%d]...\n", server->m_socketFd);
    }
    
    /*  绑定端口  */  
    if((bind(server->m_socketFd, (struct sockaddr_in*)&server->m_serverAddr, sizeof(server->m_serverAddr))) < 0)  
     {        
        printf("bind error[errno = %d]\n", errno);  
        exit(1);  
     }
    else
    {
        printf("server bind port %d success...\n", UDP_SERVER_PORT);
        printf("服务器绑定端口%d成功...\n", UDP_SERVER_PORT);
    }
/*
      开始监听绑定的端口  
    if(listen(server->m_socketFd, LISTEN_QUEUE))  
    {
        printf("Server listen error...\n");  
        exit(1); 
    }
    else
    {
        printf("Server listen success...\n");
        printf("服务器开始监听...\n");
    }
    */

    return server;
}

/*  销毁服务器  */
void DestroyUdpServer(UdpServer *server)
{
    if(server != NULL)
    {

        close(server->m_socketFd);
        free(server);
    }
}


/*
 * 服务器增加了对子进程退出时的信号处理，防止子进程数增多后带来的资源消耗
 * */
void sig_child(int signo)         /*  父进程对子进程结束的信号处理  */
{
    pid_t pid;
    int   status;
    while((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        printf("child %d terminated", pid);
        printf("子进程%d终止,,,\n", pid);
        return;
    }
}




void UdpServerRun(UdpServer *server)
{
    char                    buffer[BUFFER_SIZE];

    struct  sockaddr_in     clientAddr;  
    int                     clientLen, count;     

    while( 1 )
    {

        bzero(buffer,BUFFER_SIZE);
        

        /*  int recvfrom（int sockfd，void *buf，int len，unsigned int lags，struct sockaddr *from，int *fromlen）；  
         *
         *  from是一个struct sockaddr类型的变量，该变量保存源机的IP地址及端口号。
         *  fromlen常置为sizeof （struct sockaddr）。
         *  当recvfrom（）返回时，fromlen包含实际存入from中的数据字节数。Recvfrom（）函数返回接收到的字节数或当出现错误时返回－1，并置相应的errno。 
         * */
        count = recvfrom(server->m_socketFd, buffer, BUFFER_SIZE, 0, (struct sockaddr_in *)&clientAddr, (socklen_t *)&clientLen);  
        
        if(count < 0)
        {
            printf("UDP服务器接收信息失败...\n");
        }
        else
        {
            printf("Response from server:%s\n", buffer);  
            printf("接收到来自客户端%s的信息%s\n", inet_ntoa(clientAddr.sin_addr), buffer);
        }
    }
}

