/*************************************************************************
    > File Name: main.c
    > Author: GatieMe
    > Mail: gatieme@163.com 
    > Created Time: 2015年04月11日 星期六 18时02分26秒
 ************************************************************************/

#include "tcp.h"

int main(void)
{
    TcpServer *server = CreateTcpServer( );           /*  创建客户端  */

    TcpServerRun(server);
    


    return EXIT_SUCCESS;
}

