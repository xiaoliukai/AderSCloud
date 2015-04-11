/*************************************************************************
    > File Name: scloud-client.h
    > Author: GatieMe
    > Mail: gatieme@163.com 
    > Created Time: 2015年04月11日 星期六 11时32分28秒
 ************************************************************************/

#ifndef __SCLOUD_CLIENT_H__
#define __SCLOUD_CLIENT_H__




#include <netinet/in.h>  
#include <sys/types.h>  
#include <sys/socket.h>  

typedef struct SCloudClient
{
    /*  套接字信息  */
    struct sockaddr_in  m_serverAddr;        /*  服务器套接字地址  */
    struct sockaddr_in  m_clientAddr;        /*  客户端套接字地址  */
    int                 m_serverSocket;      /*  套接字信息  */

    /*  用户信息  */
    struct SCloudUser   m_user;              /*  用户名 */

}Client;



#endif
