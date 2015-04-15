/*************************************************************************
    > File Name: client.c
    > Author: GatieMe
    > Mail: gatieme@163.com 
    > Created Time: 2015年04月11日 星期六 12时05分02秒
 ************************************************************************/



#include "udp.h"

/*  按照user的信息初始化客户端  */
UdpClient* CreateUdpClient(User *user, char *serverAddr)
{
    UdpClient *client = NULL;
    
    /*  首先创建一个客户端结构  */
    if((client  = (UdpClient *)malloc(sizeof(UdpClient))) == NULL)
    {
        fprintf(stderr, "malloc client error...\n");    
    }

    /*  复制用户信息  */
    strcpy(user->m_name, user->m_name);     /*  用户名  */
    strcpy(user->m_pwd,  user->m_pwd);      /*  密码  */
    user->m_type = user->m_type;     /*  用户类型  */
    
    /*  服务器的地址  */
    bzero(&client->m_serverAddr, sizeof(client->m_serverAddr));   /*  全部置零  */ 
    
    client->m_serverAddr.sin_family     =   AF_INET;                      /*  internet协议族  */  
    strcpy(client->m_serverIp, serverAddr);                 /*  保存服务器IP  */
    client->m_serverAddr.sin_addr.s_addr  =   inet_addr(serverAddr);     /*  设置所连接服务器的IP */
    client->m_serverAddr.sin_port         =   htons(UDP_SERVER_PORT);               /*  设置连接的服务器端口*/
    
    /*  开始创建套接字  */
    /*  IPV4  SOCK_DGRAM 数据报套接字（UDP协议）  */
    client->m_socketFd                   =   socket(AF_INET, SOCK_DGRAM, 0);  

    if(client->m_socketFd < 0)  
    {
        printf("socket error\n");  
        exit(0);  
    }  
    
    /*  尝试连接服务器  */
    if(connect(client->m_socketFd, (struct sockaddr*)&client->m_serverAddr,sizeof(client->m_serverAddr)) < 0)  
    {
        printf("Can Not Connect To %s\n", client->m_serverIp);  
        exit(1);  
    }
    else
    {
        printf("连接服务器成功...\n");
    }


    return client;
}

/*  销毁客户端的信息  */
void DestroyUdpClient(UdpClient *client)
{
    if(client != NULL)
    {
        /*  关闭与服务器通讯的套接字  */
        close(client->m_socketFd);  
        
        free(client);   /*  销毁客户端的空间  */
    }
}

/*  客户端向服务器发送数据  */
void UdpClientSendMessage(UdpClient *client)
{


}


void UdpClientRun(UdpClient *client)
{
    int     len;
    char    buffer[BUFFER_SIZE] = "HELLO_WORLD";            
    
    //C2向C1不停地发出数据包，得到C1的回应，与C1建立连接  
    while (1)
    {  
/*
 *  sendto和recvfrom一般用于UDP协议中,但是如果在TCP中connect函数调用后也可以用.
 *  sendto（）和recvfrom（）——利用数据报方式进行数据传输  
 *  在无连接的数据报socket方式下，由于本地socket并没有与远端机器建立连接，
 *  所以在发送数据时应指明目的地址，sendto（）函数原型为：  
 *
 *  int PASCAL FAR sendto(   SOCKET s, 
 *                          const char FAR* buf, 
 *                          int len, 
 *                          int flags,
 *                          const struct sockaddr FAR* to,
 *                          int tolen);　　 
 *  参数说明:
 *  s：一个标识套接口的描述字。　 
 *  buf：包含待发送数据的缓冲区。　　 
 *  len：buf缓冲区中数据的长度。　 
 *  flags：调用方式标志位。　　 
 *  to：（可选）指针，指向目的套接口的地址。　 
 *  tolen：to所指地址的长度。   
 * */  
        /*  客户端向服务器发送数据包 */  
        len = sendto(client->m_socketFd, buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client->m_serverAddr, sizeof(client->m_serverAddr));

        if (len < 0)
        {  

            printf("sendto server failed...\n");
            printf("向服务器发送数据失败...\n");
            exit(-1);  
        }
        else 
        {
            printf("successfully send package\n");  
            printf("UDP客户端向服务器发送数据成功...\n");
        } 

        sleep(1000);
      
    }
}
