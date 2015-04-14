/*************************************************************************
    > File Name: udp.h
    > Author: GatieMe
    > Mail: gatieme@163.com 
    > Created Time: 2015年04月14日 星期二 10时24分30秒
 ************************************************************************/


#ifndef UDP_H_INCLUDE
#define UDP_H_INCLUDE

#include "config.h"
#include "user.h"







#define UDP_SERVER_PORT 6660    /*  服务器端口信息*/
#define BUFFER_SIZE     4096
#define LISTEN_QUEUE    20

#define IP_SIZE         20


typedef enum UdpClientMsgType
{
    /*  用户处理  */
    USER_REGIST =   0,          /*  用户注册  */
    USER_LOGIG  =   1,          /*  用户登录  */
    USER_QUIT   =   2,          /*  用户退出  */

    /*  查询操作  */
    READ_DIR    =   3,          /*  用户读取目录  */


    /* 文件操作  */
    PUSH_FILE   =   4,          /*  用户上传文件　*/
    PULL_FILE   =   5,          /*　用户下载文件  */
    DEL_FILE    =   6,          /*  删除文件  */
    RECOV_FILE  =   7,          /*  恢复文件  */
    
    /*  文件夹操作 v*/
    PUSH_DIR    =   8,          /*　用户上传文件夹  */
    PULL_DIR    =   9,          /*　用户下载文件夹  */
    DEL_DIR     =   10,          /*  删除文件  */
    RECOV_DIR   =   11,          /*  恢复文件  */


}UdpClientMsgType;

typedef enum UdpServerMsgType
{
    /*  用户操作  */
    USER_REGIST_SUCCESS =   0,      /*  用户注册成功  */
    USER_REGIST_FAILED  =   1,      /*  用户注册失败  */
    
    USER_LOGIN_SUCCESS  =   2,      /*  用户登录成功  */
    USER_LOGIN_FIALED   =   3,      /*  用户登录失败  */

    USER_QUIT_SUCCESS   =   4,      /*  用户退出成功  */
    USER_QUIT_FAILED    =   5,      /*  用户退出失败  */


    /*  查询操作  */
    READ_DIR_SUCCESS    =   6,      /*  用户读取文件夹成功  */
    READ_DIR_FAILED     =   7,      /*  用户读取文件夹失败  */
    
    /*  文件操作  */
    PUSH_FILE_SUCCESS   =   8,     /*  用户上传文件成功  */
    PUSH_FILE_FIALED    =   9,     /*  用户下载文件失败  */
    

    PULL_FILE_SUCCESS   =   10,     /*  用户下载文件成功  */
    PULL_FILE_FAILED    =   11,     /*  用户下载文件失败  */
    
    DEL_FILE_SUCCESS    =   12,     /*  用户删除文件成功  */ 
    DEL_FILE_FAILED     =   13,     /*  用户删除文件失败  */

    RECOV_FILE_SUCCESS  =   14,     /*  用户删除文件成功  */ 
    RECOV_FILE_FAILED   =   15,     /*  用户删除文件失败  */
    
    /*  文件夹操作  */
    PUSH_DIR_SUCCESS    =   16,     /*  用户上传文件成功  */
    PUSH_DIR_FIALED     =   17,     /*  用户下载文件失败  */
    

    PULL_DIR_SUCCESS    =   18,     /*  用户下载文件成功  */
    PULL_DOR_FAILED     =   19,     /*  用户下载文件失败  */
    
    DEL_DIR_SUCCESS     =   20,     /*  用户删除文件成功  */ 
    DEL_DIR_FAILED      =   21,     /*  用户删除文件失败  */

    RECOV_DIR_SUCCESS   =   22,     /*  用户删除文件成功  */ 
    RECOV_DIR_FAILED    =   23,     /*  用户删除文件失败  */
};

typedef struct SCloudUdpClient
{
    /*  套接字信息  */
    struct sockaddr_in  m_serverAddr;        /*  服务器套接字地址  */
    struct sockaddr_in  m_clientAddr;        /*  客户端套接字地址  */
    int                 m_socketfd;          /*  套接字信息  */
    char                m_serverIp[IP_SIZE];          /*  服务器Ip*/ 
    /*  用户信息  */
    User                m_user;              /*  用户名 */

}UdpClient;

/*  按照user的信息初始化客户端  */
UdpClient* CreateClient(User *user, char *serverIp);

/*  销毁客户端的信息  */
void DestroyUdpClient(UdpClient *client);

/***********
 *  服务器信息
 *  SCloudServer
 *
 **********/
typedef struct SCloudUdpServer
{
    /*  套接字信息  */
    struct sockaddr_in  m_serverAddr;        /*  服务器套接字地址  */
    struct sockaddr_in  m_clientAddr;        /*  客户端套接字地址  */
    int                 m_serverSocket;      /*  套接字信息  */
    
}UdpServer;

/*  创建一个服务器  */
UdpServer* CreateUdpServer( );

/*  销毁服务器  */
void DestroyUdpServer(UdpServer *server);





#endif          /*  #ifndef UDP_H_INCLUDE  */
