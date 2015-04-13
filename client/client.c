/*************************************************************************
    > File Name: client.c
    > Author: GatieMe
    > Mail: gatieme@163.com 
    > Created Time: 2015年04月11日 星期六 12时05分02秒
 ************************************************************************/



#include "tcp.h"

/*  按照user的信息初始化客户端  */
TcpClient* CreateTcpClient(User *user, char *serverAddr)
{
    TcpClient *client = NULL;
    
    /*  首先创建一个客户端结构  */
    if((client  = (TcpClient *)malloc(sizeof(TcpClient))) == NULL)
    {
        fprintf(stderr, "malloc client error...\n");    
    }

    /* 复制用户信息  */
    strcpy(user->m_name, user->m_name);     /*  用户名  */
    strcpy(user->m_pwd,  user->m_pwd);      /*  密码  */
    user->m_type = user->m_type;     /*  用户类型  */
    
    /*  */
    bzero(&client->m_serverAddr, sizeof(client->m_serverAddr));   /*  全部置零  */ 
    
    client->m_serverAddr.sin_family     =   AF_INET;                      /*  internet协议族  */  
    strcpy(client->m_serverIp, serverAddr);                 /*  保存服务器IP  */
    client->m_serverAddr.sin_addr.s_addr  =   inet_addr(serverAddr);     /*  设置所连接服务器的IP */
    client->m_serverAddr.sin_port         =   htons(TCP_SERVER_PORT);               /*  设置连接的服务器端口*/
    
    /* 开始创建套接字  */
    client->m_socketFd                   =   socket(AF_INET,SOCK_STREAM,0);  

    if(client->m_socketFd < 0)  
    {
        printf("socket error\n");  
        exit(0);  
    }  
    
    /*  尝试连接服务器  */
    if(connect(client->m_socketFd, (struct sockaddr*)&client->m_serverAddr,sizeof(client->m_serverAddr)) < 0)  
    {
        printf("Can Not Connect To %s\n", client->m_serverIp);  
        exit(1);  
    }
    else
    {
        printf("连接服务器成功...\n");
    }


    return client;
}

/*  销毁客户端的信息  */
void DestroyTcpClient(TcpClient *client)
{
    if(client != NULL)
    {
        /*  关闭与服务器通讯的套接字  */
        close(client->m_socketFd);  
        
        free(client);   /*  销毁客户端的空间  */
    }
}


/* 客户端将文件上传到服务器上 */
void TcpClientPushFile(TcpClient *client, char *filePath)
{
    FILE    *stream;
    char    buffer[BUFFER_SIZE];
    char    filename[MAX_FILENAME_SIZE];
    int     count = 0;  
    
    /* 先将文件名发送给服务器 
     * 2015-4-13 21:38 Modify
     * 发送文件名时只需要发送filePath最后的文件名filename就可以了
     * */
    bzero(buffer, BUFFER_SIZE);  
    strcpy(filename, strrchr(filePath, '/') + 1);
    strncpy(buffer, filename, strlen(filename) > MAX_FILENAME_SIZE ? MAX_FILENAME_SIZE : strlen(filename)); 
    count = send(client->m_socketFd, buffer, BUFFER_SIZE, 0);  
    printf(" 客户端待上传待文件名[%s]..\n", filename);

    
    if(count < 0)
    {
        perror("Send file information");  
        exit(1);  
    }

    /*  打开文件流  */
    if((stream = fopen(filePath, "r")) == NULL)  
    {  
        printf("Can't open the file [%s]\n", filePath);  
        exit(1);  
    }
    else
    {
        printf("客户端打开文件成功\n");
    }

    printf("正在向服务器传上传文件...\n");  
    count = 0;  
    
    /*  清空缓冲区  */
    bzero(buffer, BUFFER_SIZE);  

    /*  不断读取并发送数据  */ 
    while((count = fread(buffer, 1, BUFFER_SIZE, stream)) > 0)  
    {  
        // printf("count =%d\n", count);  
        if(send(client->m_socketFd, buffer, count, 0) < 0)  
        {  
            printf("send file error...\n");  
            break;  
        }  

        bzero(buffer, BUFFER_SIZE);  /*  再次将缓冲区清空  */  
    }  
    
    printf("向服务器发送文件成功...\n");

    /* 传送完毕后， 关闭文件流  */
    if(fclose(stream))  
    {  
        printf("file close error\n");  
        exit(1);  
    }
    else
    {
        printf("关闭文件流成功...\n");
    }
   

    /*  关闭与服务器通讯的套接字  */
    close(client->m_socketFd);  
    
}  

/* 从服务器上下载文件  */
void TcpClientPullFile(TcpClient *client)
{
    char    buff[BUFFER_SIZE];  
    char    filename[MAX_FILENAME_SIZE];  
    int     count, writeLength, dataLength;  
    FILE    *stream;
    bzero(buff,BUFFER_SIZE);  
  

    /*  首先获取服务器发送过来的文件名  */
    count = recv(client->m_socketFd, buff, BUFFER_SIZE, 0);  
    
    if(count < 0)  
    {  
        perror("获取文件名失败...\n");  
        exit(1);  
    }  
    
    strncpy(filename, buff, strlen(buff) > MAX_FILENAME_SIZE ? MAX_FILENAME_SIZE : strlen(buff));  
  
    /*  开始接收文件  */
    printf("Preparing download file : %s from %s \n", filename, client->m_serverIp);   
    printf("准备下载来自服务器%s的文件%s...\n", filename, client->m_serverIp);

    /*  打开文件流  */  
    if((stream = fopen(filename,"wb+")) == NULL)  
    {
        perror("create file %s error...\n");  
        perror("创建文件失败...\n");
        exit(1);  
    }

    bzero(buff, BUFFER_SIZE);          /*  清空缓冲区  */  
    dataLength = 0;  
    while((dataLength = recv(client->m_socketFd, buff, BUFFER_SIZE, 0)) != 0)   
    {  
        if(dataLength < 0)  /* 如果接收文件失败  */ 
        {  
            perror("download error...\n");  
            perror("下载文件失败...\n");
            exit(1);  
        }  


        /*  将接收到的文件数据写入文件中  */
        writeLength = fwrite(buff, sizeof(char), dataLength, stream);     
        if(writeLength < dataLength)   /*  如果写入的数据比实际接收到的数据少  */  
        {  
            perror("file write error...\n");
            perror("写入文件失败...\n");
            exit(1);  
        }  
        
        bzero(buff,BUFFER_SIZE);               /* 清空缓冲区  */
    }  
    printf("下载来自服务器%s的文件%s成功\n", filename, client->m_serverIp);
    printf("Receieved file:%s from %s finished!\n",filename, client->m_serverIp);  
    
    fclose(stream);             /*  关闭文件流 */
}
