#ifndef _XPSOCKET_HEADER_
#define _XPSOCKET_HEADER_

#include <iostream>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/epoll.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <arpa/inet.h>

#include "SingleTon.h"

class XPSOCKET
{
private:
    int _iDomain;                               //with : AF_INET
    int _isock;                                 //with : sock file handler
    int _listencount;                           //with : count of socket listen
    int _addrlen;
    bool _blockstatus;                          //with : block status : default = false
    struct sockaddr_in selfaddr, remoteaddr;    //with : internet socket address struct define
    enum { INVALID_FAILED = 0 };                //with : sock link failed.
    enum { MAX_BUFF_SIZE = 1024*8 };              //with : Max of size once read.
    char buf[MAX_BUFF_SIZE];                    //with : read buf area
    std::string getPeerIpaddress(int remotefd); //with : method used to get peer ipaddress
public:
    XPSOCKET();
    XPSOCKET(int listencount);
    ~XPSOCKET();
    void Create(int SocketType, int Domain, int flags);             // create socket 
    void Close();                                                   // close socket
    void Setnonblock();                                             // set non block
    void Setnonblock(int epollsubfd);                               // set non block
    void InitSocket(const void *selfip, int port, int iplength);    // initilaize data
    void Bindsocket();                                              // bind socket
    void Listensocket();                                            // listen socket 
    int Acceptlink();                                               // accept remote link 
    std::string ReadData(int remotefd);                             // read socket data
    void WriteData(int remotefd, const std::string & data);         // send cilent data (non block)
    void SendData(int remotefd, int flags);                         // send client data (block)
    int * getserverfd();                                            // use method to get server file handler
};

#endif

typedef SINGLETON<XPSOCKET> newsocket;
