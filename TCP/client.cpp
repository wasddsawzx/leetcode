#include<winsock2.h>
#include<stdio.h>
#include<iostream>
#include<thread>
#include<mutex>
#pragma comment(lib,"ws2_32.lib")
using namespace std;
using namespace std::this_thread;
/*
服务器端：

其过程是首先服务器方要先启动，并根据请求提供相应服务：

（1）打开一通信通道并告知本地主机，它愿意在某一公认地址上的某端口（如FTP的端口可能为21）接收客户请求；

（2）等待客户请求到达该端口；

（3）接收到客户端的服务请求时，处理该请求并发送应答信号。接收到并发服务请求，要激活一新进程来处理这个客户请求（如UNIX系统中用fork、exec）。新进程处理此客户请求，并不需要对其它请求作出应答。服务完成后，关闭此新进程与客户的通信链路，并终止。

（4）返回第（2）步，等待另一客户请求。

（5）关闭服务器

*/

void func(SOCKET serConn)
{   
    
}

int main()
{
    WORD myVersionRequest;
    WSADATA wsaData;

    myVersionRequest = MAKEWORD(1,1);
    int err;
    err = WSAStartup(myVersionRequest,&wsaData);

    if(!err)
    {
        printf("已经打开套接字!");
    }
    else
    {
        printf("套接字未打开！");
        return 0;
    }

    SOCKET serSocket = socket(AF_INET,SOCK_STREAM,0);

    SOCKADDR_IN addr;

    addr.sin_family = AF_INET;
    addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);

    addr.sin_port = htons(6000);

    bind(serSocket,(SOCKADDR*)&addr,sizeof(SOCKADDR));

    listen(serSocket,5);

    SOCKADDR_IN clientsocket;
    int len = sizeof(SOCKADDR);
    // while(1)
    // {
    //     
    //     thread th(func,serConn);
    // }
    SOCKET serConn = accept(serSocket,(SOCKADDR*)&clientsocket,&len);
    while(1)
    {
        
        char sendBuf[100];
        sprintf(sendBuf,"welcom %s to bejing",inet_ntoa(clientsocket.sin_addr));
        send(serConn,"Hello,this is client",strlen("hello ,this is client")+1,0);
        char receiveBuf[100];
        recv(serConn,receiveBuf,sizeof(receiveBuf)+1,0);
        cout<<receiveBuf<<endl;
        Sleep(1);
    }
    
    
    // printf("%s\n",receiveBuf);
    // closesocket(serConn);
    closesocket(serSocket);
    WSACleanup();
    return 0;



}