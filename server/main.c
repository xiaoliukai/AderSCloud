/*************************************************************************
    > File Name: main.c
    > Author: GatieMe
    > Mail: gatieme@163.com 
    > Created Time: 2015年04月11日 星期六 18时02分26秒
 ************************************************************************/

#include "scloud.h"

int main(void)
{
    Server *server = CreateServer( );           /*  创建客户端  */

    ServerRun(server);
    


    return EXIT_SUCCESS;
}

