#include<winsock2.h>
#include<thread>
#include<stdio.h>
#include<iostream>
#pragma comment(lib,"ws2_32.lib")
using namespace std;


/*
客户端：

（1）打开一通信通道，并连接到服务器所在主机的特定端口；

（2）向服务器发服务请求报文，等待并接收应答；继续提出请求......

（3）请求结束后关闭通信通道并终止。

*/


int main()
{
    int err;
    WORD versionRequire;
    WSADATA wsaData;
    // 检查协议版本
    versionRequire = MAKEWORD(1,1);
    err = WSAStartup(versionRequire,&wsaData);

    if(!err)
    {
        cout<<"客户端套接字已经打开！\n"<<endl;
    }
    else
    {
        cout<<"客户端套接字打开失败！\n"<<endl;
        return 0;
    }

    SOCKET clientSocket = socket(AF_INET,SOCK_STREAM,0);

    SOCKADDR_IN clientsock_in;
    clientsock_in.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    clientsock_in.sin_family = AF_INET;
    clientsock_in.sin_port = htons(6000);

    connect(clientSocket,(SOCKADDR*)&clientsock_in,sizeof(SOCKADDR));
    while(1)
    {
        char receiveBuf[100];
        recv(clientSocket,receiveBuf,101,0);
        cout<<receiveBuf<<endl;

        send(clientSocket,"this is client",strlen("hello, this is client")+1,0);
        Sleep(1);
    }
    

    closesocket(clientSocket);
    WSACleanup();
    return 0;

}