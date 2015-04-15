/*************************************************************************
    > File Name: main.c
    > Author: GatieMe
    > Mail: gatieme@163.com 
    > Created Time: 2015年04月11日 星期六 18时02分26秒
 ************************************************************************/

#include "udp.h"

int main(void)
{
    UdpServer *server = CreateUdpServer( );           /*  创建客户端  */

    UdpServerRun(server);
    


    return EXIT_SUCCESS;
}

