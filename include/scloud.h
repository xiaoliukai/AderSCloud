#ifndef  SCLOUD_H_INCLUDE
#define  SCLOUD_H_INCLUDE


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




#define MAX_FILENAME_SIZE    256

/***********
 *  用户信息
 *  SCloudUser
 *
 **********/
#define MAX_USERNAME    81      /*  用户名的最大长度  */
#define MAX_PASSWORD    81      /*  用户密码的最大长度  */


/*  用户的类型以及权限问题  */
typedef enum SCloudUserType
{
    GUEST   =   0,      /*  来宾  */

    USER    =   1,      /*  普通用户  */

    ADMIN   =   2,      /*  administrator管理员  */

}UserType;

typedef struct SCloudUser
{
    char        m_name[MAX_USERNAME];   /*  用户名  */
    char        m_pwd[MAX_PASSWORD];    /*  密码    */
    UserType    m_type;                 /*  用户类型以及权限  */

}User;


/*  创建用户  */
void CreateUser(char *name, char *pwd, UserType type);

/*  删除用户  */
void DestroyUser(User *user);



/***********
 *  客户端信息
 *  SCloudClient
 *
 **********/

#define SERVER_PORT     6666    /*  服务器端口信息*/
#define BUFFER_SIZE     4096
#define LISTEN_QUEUE    20

#define IP_SIZE         20

typedef struct SCloudClient
{
    /*  套接字信息  */
    struct sockaddr_in  m_serverAddr;        /*  服务器套接字地址  */
    struct sockaddr_in  m_clientAddr;        /*  客户端套接字地址  */
    int                 m_socketFd;          /*  套接字信息  */
    char                m_serverIp[IP_SIZE];          /*  服务器Ip*/ 
    /*  用户信息  */
    User                m_user;              /*  用户名 */

}Client;

/*  按照user的信息初始化客户端  */
Client* CreateClient(User *user, char *serverIp);

/*  销毁客户端的信息  */
void DestroyClient(Client *client);

/*  客户端将文件上传到服务器上 */
void ClientPushFile(Client *client, char *filePath);


/***********
 *  服务器信息
 *  SCloudServer
 *
 **********/
typedef struct SCloudServer
{
    /*  套接字信息  */
    struct sockaddr_in  m_serverAddr;        /*  服务器套接字地址  */
    struct sockaddr_in  m_clientAddr;        /*  客户端套接字地址  */
    int                 m_serverSocket;      /*  套接字信息  */
    
}Server;

/*  创建一个服务器  */
Server* CreateServer( );

/*  销毁服务器  */
void DestroyServer(Server *server);


#endif      // #define __SCLOUD_H__
