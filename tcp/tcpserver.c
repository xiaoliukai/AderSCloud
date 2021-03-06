/*************************************************************************
    > File Name: server.c
    > Author: GatieMe
    > Mail: gatieme@163.com 
    > Created Time: 2015年04月11日 星期六 16时22分10秒
 ************************************************************************/

#include "tcp.h"



/*  创建一个服务器  */
TcpServer* CreateTcpServer( )
{
    TcpServer *server = NULL;
   
    /*  首先开辟服务器的空间  */
    if((server = (TcpServer *)malloc(sizeof(TcpServer))) == NULL)
    {
        fprintf(stderr, "malloc server failed...\n'");
    }

    bzero(&server->m_serverAddr,sizeof(server->m_serverAddr));/*  全部置零  */  
    
    /* 设置地址相关的属性 */
    server->m_serverAddr.sin_family         =   AF_INET;  
    server->m_serverAddr.sin_addr.s_addr    =   htons(INADDR_ANY);  
    server->m_serverAddr.sin_port           =   htons(TCP_SERVER_PORT);  
    
    /*  创建套接字  */
    server->m_socketFd = socket(AF_INET, SOCK_STREAM, 0);  
    if(server->m_socketFd < 0)   
    {
        perror("socket create error\n");  
        exit(1);  
    }
    else
    {
        printf("socket create success...\n");
        printf("创建套接字成功...\n");
    }
    
    /*  绑定端口  */  
    if(bind(server->m_socketFd, (struct sockaddr*)&server->m_serverAddr, sizeof(server->m_serverAddr)) > 0)  
    {        
        perror("bind error\n");  
        exit(1);  
    }
    else
    {
        printf("server bind port %d success...\n", TCP_SERVER_PORT);
        printf("服务器绑定端口%d成功...\n", TCP_SERVER_PORT);
    }

    /*  开始监听绑定的端口  */
    if(listen(server->m_socketFd,LISTEN_QUEUE))  
    {
        printf("Server listen error...\n");  
        exit(1); 
    }
    else
    {
        printf("Server listen success...\n");
        printf("服务器开始监听...\n");
    }

    return server;
}

/*  销毁服务器  */
void DestroyTcpServer(TcpServer *server)
{
    if(server != NULL)
    {

        close(server->m_socketFd);
        free(server);
    }
}


/*
 * 服务器增加了对子进程退出时的信号处理，防止子进程数增多后带来的资源消耗
 * */
void sig_child(int signo)         /*  父进程对子进程结束的信号处理  */
{
    pid_t pid;
    int   status;
    while((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        printf("child %d terminated", pid);
        printf("子进程%d终止,,,\n", pid);
        return;
    }
}



/* 服务器接收从客户端传送来的文件  */
void
TcpServerPullFile(
            TcpServer   *server,                 /*  服务器的信息  */
            struct      sockaddr_in clientAddr,  /*  与之通信的客户端的信息  */
            int         connfd)        /* 服务器与客户端通讯的套接字文件  */
{
    char    buffer[BUFFER_SIZE];  
    char    filename[MAX_FILENAME_SIZE];        
    // 定义文件流  
    FILE    *stream;

    int     count;              /*  发送文件名的字节数目  */
    int     dataLength;         /*  接收到的数据大小  */
    int     writeLength;        /* 实际写入的数据大小  */
    int     flag = 0; 
    
    bzero(buffer, BUFFER_SIZE);  
    /*
     *  向客户端提示输入文件路径提示...
     *  
     * strcpy(buffer, "请输入要传输的文件的完整路径：");  
    strcat(buffer, "\n");  
       
    send(new_server_socket, buffer, BUFFER_SIZE, 0);  
    bzero(buffer, BUFFER_SIZE);  
    */
    
    /*  首先获取客户端发送过来的文件名  */
    count = recv(connfd, buffer, BUFFER_SIZE, 0);  
    
    if(count < 0)  
    {  
        perror("获取文件名失败...\n");  
        exit(1);  
    }
    else
    {

        strncpy(filename, buffer, strlen(buffer) > MAX_FILENAME_SIZE ? MAX_FILENAME_SIZE : strlen(buffer));  
    
        printf("获取客户端发送过来的文件名成功...\n");
        printf("文件名[%s]\n", filename);
    }
    //  服务器接受数据, 首先打开一个文件流           
    if((stream = fopen(filename, "w")) == NULL)  
    {
        perror("file open error...\n");
        exit(1);  
    }
    else  
    {
        bzero(buffer,BUFFER_SIZE);  
    }  

    printf("正在接收来自%s的文件....\n",inet_ntoa(clientAddr.sin_addr));  
           
    dataLength = 0;
    
    
    /*  先将数据接受到缓冲区buffer中，再写入到新建的文件中  */ 
    while((dataLength = recv(connfd, buffer, BUFFER_SIZE, 0)) > 0)  
    {  
    
        flag++;  
                
        if(flag == 1)  
        {  
            printf("正在接收来自%s的文件....\n",inet_ntoa(clientAddr.sin_addr));      
        }  
              
        if(dataLength < 0)  
        {  
            printf("接收错误i\n");  
            exit(1);  
        }  

        /*  向文件中写入数据  */ 
        writeLength = fwrite(buffer, sizeof(char), dataLength, stream);  
               
        if(writeLength != dataLength)  
        {  
             printf("file write failed\n");  
             exit(1);  
        }  
        bzero(buffer,BUFFER_SIZE);  
    }  
            
    if(flag > 0) 
    {
        printf("%s的文件传送完毕\n", inet_ntoa(clientAddr.sin_addr));  
    }
    if(flag==0)  
    {
        printf("%s的文件传输失败\n", inet_ntoa(clientAddr.sin_addr));  
    }
          
    fclose(stream);  
    //rename("data",inet_ntoa(clientAddr.sin_addr));  
    
}



/*  服务器将文件发送到客户端  
 *
 *  当用户选择了下载文件后，服务器将执行此操作
 *
 *  */
void TcpServerPushFile(
                    TcpServer   *server,                 /*  服务器结构体  */ 
                    struct      sockaddr_in clientAddr,  /*  与之通信的客户端的信息  */
                    int         connfd,                  /*  服务器与客户端通讯的套接字文件  */
                    char        *filePath)              /*  带发送至客户端的文件路径  */
{
    //send file imformation  
        
    char    buff[BUFFER_SIZE];  
    char    filename[MAX_FILENAME_SIZE];
    int     count;  
    FILE    *stream;
        
    
    /* 先将文件名发送给客户端 
     * 2015-4-13 21:38 Modify
     * 发送文件名时只需要发送filePath最后的文件名filename就可以了
     * */
    bzero(buff, BUFFER_SIZE);  
    strcpy(filename, strrchr(filePath, '/') + 1);
    strncpy(buff, filename, strlen(filename) > MAX_FILENAME_SIZE ? MAX_FILENAME_SIZE : strlen(filename)); 
    count = send(connfd, buff, BUFFER_SIZE, 0);  
    printf("服务器待发送的文件名[%s]..\n", filename);

    if(count < 0)
    {
        perror("Send file information");  
        exit(1);  
    }  
          
    /*  服务器开始读取并且发送文件 ： */   
    if((stream = fopen(filePath, "rb")) == NULL)  
    {  
        printf("File :%s not found!\n",filePath);  
    }  
    printf("服务器打开文件成功...\n");
    printf("正在向客户端发送文件...\n");
    bzero(buff,BUFFER_SIZE);  
        
    int fileBlockLength = 0;  
    while((fileBlockLength = fread(buff, sizeof(char), BUFFER_SIZE, stream)) > 0)  
    {  
        printf("读取了:%d个数据...\n",fileBlockLength);  
        if(send(connfd, buff, fileBlockLength, 0) < 0)  
        {  
            perror("Send file error...\n");
            perror("向客户端发送文件失败...\n");
            exit(1);  
        }  
        
        bzero(buff,BUFFER_SIZE);     
    }  
    
    fclose(stream);  
    printf("Transfer file finished !\n");   

        //close(connfd);          /*  关闭与客户端通信的套接字  */  
}  




/*  服务器运行的函数  */
void TcpServerRun(TcpServer *server)
{

    signal(SIGCHLD, sig_child);                /*  子进程退出的信号处理  */

    while( 1 )
    {
        pid_t pid;  
        struct sockaddr_in clientAddr;         /*  存储连接至服务器的客户端  */  
        socklen_t length = sizeof(clientAddr);  
     
        /* accept返回一个新的套接字与客户端进行通信  */
        int connfd = accept(server->m_socketFd, (struct sockaddr*)&clientAddr, &length);  
    
        if(connfd == -1)  
        {  
            printf("accept error\n");  
            continue;  
        }
        else
        {  
            printf("客户端 %s 连接成功\n", inet_ntoa(clientAddr.sin_addr));  
            pid = fork( ); 
            if(pid < 0)
            {
                perror("fork error...\n");
                perror("创建子进程失败...\n");
                exit(1);
            }
            else if(pid == 0)       /*  在子进程中处理客户端的请求  */  
            {  
                printf("用于与客户端%s通信的子进程%d", inet_ntoa(clientAddr.sin_addr), getpid( ));
                ///////////////////////////////////////////
                //
                //  在这里填写服务器处理的代码
                //
                ///////////////////////////////////////////
                TcpServerPullFile(server, clientAddr, connfd);
            }
            else
            {
                ///////////////////////////////////////////
                //
                //  在这里填写父进程的处理
                //
                ///////////////////////////////////////////
                close(connfd);
            }
        }
    }
}

