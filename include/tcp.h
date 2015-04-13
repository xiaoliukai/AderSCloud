#ifndef  TCP_H_INCLUDE
#define  TCP_H_INCLUDE


#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  
#include <string.h> 

#include <netinet/in.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <sys/wait.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>


#include "user.h"






/***********
 *  客户端信息
 *  SCloudTcpClient
 *
 **********/

#define TCP_SERVER_PORT     6666    /*  服务器端口信息*/
#define BUFFER_SIZE     4096
#define LISTEN_QUEUE    20

#define IP_SIZE         20

typedef struct SCloudTcpClient
{
    /*  套接字信息  */
    struct sockaddr_in  m_serverAddr;        /*  服务器套接字地址  */
    struct sockaddr_in  m_clientAddr;        /*  客户端套接字地址  */
    int                 m_socketFd;          /*  套接字信息  */
    char                m_serverIp[IP_SIZE];          /*  服务器Ip*/ 
    /*  用户信息  */
    User                m_user;              /*  用户名 */

}TcpClient;

/*  按照user的信息初始化客户端  */
TcpClient* CreateTcpClient(User *user, char *tcpServerIp);

/*  销毁客户端的信息  */
void DestroyTcpClient(TcpClient *tcpClient);

/*  客户端将文件上传到服务器上 */
void TcpClientPushFile(TcpClient *client, char *filePath);


/***********
 *  服务器信息
 *  SCloudTcpServer
 *
 **********/
typedef struct SCloudTcpServer
{
    /*  套接字信息  */
    struct sockaddr_in  m_serverAddr;        /*  服务器套接字地址  */
    struct sockaddr_in  m_clientAddr;        /*  客户端套接字地址  */
    int                 m_serverSocket;      /*  套接字信息  */
    
}TcpServer;

/*  创建一个服务器  */
TcpServer* CreateTcpServer( );

/*  销毁服务器  */
void DestroyTcpServer(TcpServer *tcpServer);


#endif      // #define __SCLOUD_H__
