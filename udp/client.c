#include "tcp.h"
 


int main(void)
{

    User user = {"gatieme", "pan08917me", USER};
    
    TcpClient *client = CreateTcpClient(&user, "127.0.0.1");

    TcpClientPushFile(client, "./file/test");


    return 0;  
}  
