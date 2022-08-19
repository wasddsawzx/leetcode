#include<winsock2.h>
#include<thread>
#include<stdio.h>
#include<iostream>
#include<mutex>
#include <windows.h>  
#pragma comment(lib,"ws2_32.lib")
using namespace std;
using namespace std::this_thread;

mutex Mutex;
int connectOk=0;

void client()
{
    
    int err;
    WORD versionRequire;
    WSADATA wsaData;
    int ticket =100;
    versionRequire = MAKEWORD(1,1);
    err = WSAStartup(versionRequire,&wsaData);

    if(!err)
    {
        cout<<"客户端已经打开\n"<<endl;
    }
    else{
        cout<<"客户端打开失败\n"<<endl;
        throw "客户端打开失败";
    }
    SOCKET clientSocket = socket(AF_INET,SOCK_STREAM,0);

    SOCKADDR_IN clientsock_in;
    clientsock_in.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    clientsock_in.sin_family = AF_INET;
    clientsock_in.sin_port = htons(6000);
    while (connectOk ==0)
    {
        
    }

    int ret = connect(clientSocket,(SOCKADDR*)&clientsock_in,sizeof(SOCKADDR));
    cout<<"ret: "<<ret<<endl;
    cout<<"wsa error: "<<WSAGetLastError()<<endl;
    
    while(ticket--)
    {
        
        lock_guard<mutex> lck(Mutex);
        // Mutex.lock();
        char receiveBuf[100];
        int ret2 = recv(clientSocket,receiveBuf,sizeof(receiveBuf),0);
        cout<<"ret2: "<<ret2<<endl;
        cout<<receiveBuf<<endl;
        send(clientSocket,"Hello,this is client",strlen("hello ,this is client")+1,0);
        Sleep(1);
        // Mutex.unlock();
        // cout<<ticket--<<endl;
        
    }
    
    
    
    
    closesocket(clientSocket);
    WSACleanup();
    return;

}

void server()
{
    WORD myVersionRequest;
    WSADATA wsaData;
    int ticket =100;
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
        throw "open failed";
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

    connectOk = 1;
    
    SOCKET serConn = accept(serSocket,(SOCKADDR*)&clientsocket,&len);
    cout<<"accept: "<<serConn<<endl;

    while(1)
    {
        
        lock_guard<mutex> lck(Mutex);
        char sendBuf[100];
        sprintf(sendBuf,"welcom %s to bejing",inet_ntoa(clientsocket.sin_addr));
        int ret = send(serConn,sendBuf,strlen(sendBuf)+1,0);
        cout<<"ret: "<<ret<<endl;
        // while (1)
        // {
        Sleep(1);
        // }
        char receiveBuf[100]={0};
        recv(serConn,receiveBuf,sizeof(receiveBuf)+1,0);
        cout<<receiveBuf<<endl;
        // Sleep(1);
        // cout<<ticket--<<endl;
        
        
    }
    closesocket(serConn);
        // closesocket(serSocket);
    WSACleanup();
    // printf("%s\n",receiveBuf);
    
    return ;
}


int main()
{
    thread th1(server),th2(client);
    th2.join();
    th1.join();
    return 0;
    

}