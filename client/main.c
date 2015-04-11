#include "scloud.h"
 


int main(void)
{

    User user = {"gatieme", "pan08917me", USER};
    
    Client *client = CreateClient(&user, "127.0.0.1");

    ClientPushFile(client, "./file/test");


    return 0;  
}  
