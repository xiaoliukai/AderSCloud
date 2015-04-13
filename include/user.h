#ifndef  USER_H_INCLUDE
#define  USER_H_INCLUDE


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


#endif
