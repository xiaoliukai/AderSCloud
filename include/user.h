#ifndef  USER_H_INCLUDE
#define  USER_H_INCLUDE


#include "config.h"
#include "user.h"





#define MAX_FILENAME_SIZE    256



/***********
 *  用户信息
 *  SCloudUser
 *
 **********/
#define MAX_USERNAME    81      /*  用户名的最大长度  */
#define MAX_PASSWORD    81      /*  用户密码的最大长度  */



/*  用户默认最大可用磁盘空间   
 *  默认单位是MB：
 *  */
#define MAX_GUEST_SPACE_SIZE    0           /*  普通来宾用户默认的空间是0G  */
#define MAX_USER_SAPCE_SIZE     1           /*  普通用户默认的云盘空间是1G  */
#define MAX_ADMIN_SPACE_SIZE    5           /*  管理员用户默认的云盘空间是5G  :w*/

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


    double      m_totalSpaceSize;       /*  用户的共计云盘使用空间  */
    double      m_usedSpaceSize;        /*  已经使用的云盘空间  */
    double      m_freeSpaceSize;        /*  空闲使用空间  */
}User;


/*  创建用户  */
void CreateUser(char *name, char *pwd, UserType type);

/*  删除用户  */
void DestroyUser(User *user);


#endif
