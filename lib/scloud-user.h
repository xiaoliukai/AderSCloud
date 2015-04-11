/*************************************************************************
    > File Name: scloud-user.h
    > Author: GatieMe
    > Mail: gatieme@163.com 
    > Created Time: 2015年04月11日 星期六 11时11分15秒
 ************************************************************************/

#ifndef __SCLOUD_USER_H__
#define __SCLOUD_USER_H__


#define MAX_USERNAME    81      /*  用户名的最大长度  */
#define MAX_PASSWORD    81      /*  用户密码的最大长度  */



/*  用户的类型以及权限问题  */
typedef struct SCloudUserType
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
void CreateUser( );

/*  删除用户  */
void DestroyUser( );
#endif  // __SCLOUD_USER_H__


