#include "udp.h"
 


int main(void)
{

    User user = {"gatieme", "pan08917me", USER};
    
    UdpClient *client = CreateUdpClient(&user, "127.0.0.1");

    UdpClientRun(client);

    return 0;  
}  
