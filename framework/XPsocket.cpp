#include "XPsocket.h"
#include "XPhttp.h"

XPSOCKET::XPSOCKET()
{
    _iDomain = 0;
    _isock = 0;
    _blockstatus = false;
    _listencount = 5000;
    _addrlen = 0;
}

XPSOCKET::XPSOCKET(int listencount)
{
    _iDomain = 0;
    _isock = 0;
    _blockstatus = false;
    _listencount = listencount;
    _addrlen = 0;
}

XPSOCKET::~XPSOCKET()
{
    printf("free initilaize.\n");
}

/* public method */

/* 
This method used to create a new socket. 
usage:  sockettype = socket agreement
        domain = socket AF_INET
        flags = socket flag
*/
void XPSOCKET::Create(int SocketType, int Domain, int flags)
{
    _iDomain = Domain;
    _isock = socket(_iDomain, SocketType, flags);
    
    if (_isock < 0)
    {
        _isock = INVALID_FAILED;
        perror("[XPSOCKET :: Create] Create socket Failed.\n");
    }

}

void XPSOCKET::Close()
{
    if (_isock != INVALID_FAILED)
    {
        close(_isock);
        _isock = INVALID_FAILED;
    } 
}

/*
This method used to set file handler into non block status
using fcntl.h to achieve
care about F_GETFL and F_SETFL
each step error will throw corresponding message.
*/
void XPSOCKET::Setnonblock()
{
    int __getval = 0;
    int __setval = 0;

    __getval = fcntl(_isock, F_GETFL, 0);
    if (__getval == -1)
    {
        perror("[XPSocket :: setnonblock] fcntl.F_GETFL error.\n");
    }

    if (_blockstatus == false)
    {
        __getval |= O_NONBLOCK;
    }

    __setval = fcntl(_isock, F_SETFL, __getval);
    if (__setval == -1)
    {
        perror("[XPSocket :: setnonblock] fcntl.F_SETFL error.\n");
    } 

}

/*
This method used to set file handler outside into non block
will input epoll sub file handler or others
using fcntl.h to achieve
care about F_GETFL and F_SETFL
each step error will throw corresponding message.
*/
void XPSOCKET::Setnonblock(int epollsubfd)
{
    int __getval = 0;
    int __setval = 0;

    __getval = fcntl(epollsubfd, F_GETFL, 0);
    if (__getval == -1)
    {
        perror("[XPSocket :: setnonblock] fcntl.F_GETFL error.\n");
    }

    if (_blockstatus == false)
    {
        __getval |= O_NONBLOCK;
    }

    __setval = fcntl(epollsubfd, F_SETFL, __getval);
    if (__setval == -1)
    {
        perror("[XPSocket :: setnonblock] fcntl.F_SETFL error.\n");
    }

}

/*
This method used to set init socket 
can input ipaddress and port
ip will be change into internet host long
port wll be change into internet host short
*/
void XPSOCKET::InitSocket(const void * selfip, int port, int iplength)
{
    /* initilaize selfaddr. */
    memset(&selfaddr, 0, sizeof(struct sockaddr_in *));

    /* analyst selfip detail. */
    char tmp[iplength];
    memcpy(tmp, selfip, iplength);

    /* initilaize variable. */
    selfaddr.sin_family = AF_INET;
    selfaddr.sin_port = htons(port);
    selfaddr.sin_addr.s_addr = htonl(INADDR_ANY);

}

/*
This method used to bind socket 
deal with process inside.
*/
void XPSOCKET::Bindsocket()
{
    /* tmp variable binding */
    int binding;
    
    /* port reuse */
    const int reuse = 1;
    setsockopt(_isock, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse));
    setsockopt(_isock, IPPROTO_TCP, TCP_NODELAY, (const char*)&reuse, sizeof(reuse));

    /* add recv buf */
    int recv_buf_len = 1*1024*1024; 
    setsockopt(_isock, SOL_SOCKET, SO_RCVBUF, (const char*)&recv_buf_len, sizeof(recv_buf_len));

    binding = bind(_isock, (struct sockaddr *)&selfaddr, sizeof(selfaddr));    
    if (binding == -1)
    {
        perror("[XPSocket :: Bindsocket] failed.\n");
    }
}

/*
This method used to listen socket
the number of count is define in private _listencount
*/
void XPSOCKET::Listensocket()
{
    /* tmp variable listen */
    int listening;
    
    listening = listen(_isock, _listencount);
    if (listening == -1)
    {
        perror("[XPSOCKET :: Listensocket] Failed.");
    }
}

/*
This method used to accept remote link
need 3 important variables
1. listen socket file handler
2. remoteaddr socket addr
3. size_t addrlen 
*/
int XPSOCKET::Acceptlink()
{
    int tmpacc;
    
    tmpacc = accept(_isock, (struct sockaddr *)&remoteaddr, (socklen_t *)&_addrlen);

    return tmpacc;
}

/*
This method used to recv remote data
need 3 variables
1. remote file handler
2. buffer (private)
3. buffer size (private)
*/
std::string XPSOCKET::ReadData(int remotefd)
{       
    /* statement about return. */
    std::string returnbuf;
    /* tmp int initilaize. */
    int now = 0;
    int nread = 0;
    int offset=0;
    struct sockaddr_in remotetmp;
    unsigned int len = sizeof(remotetmp);

    /* tmp buf set. */
    char *tmp_header;
    tmp_header = (char*)malloc(8*sizeof(char));
    memset(tmp_header, 0, 8*sizeof(char));

    memset(buf, 0, MAX_BUFF_SIZE);

    HttpAction httpdoing;

    /* using httpAction header. */
    while(1)
    {
        //int length = recv(remotefd, tmp_header, 8, MSG_WAITALL);
        int length = recv(remotefd, tmp_header, 8, MSG_DONTWAIT);
        if (length > 0)
        {
            usleep(10);
	    if (errno == EAGAIN || errno == EINTR || errno == EWOULDBLOCK)
            {
                memset(tmp_header, 0, sizeof(tmp_header));
                break;
            }
	    else
            {
                memcpy(buf+offset, tmp_header, length);
                offset += length;
                //memset(tmp_header, 0, sizeof(tmp_header));
            }
        }
	else if (length == 0)
        {
            memset(tmp_header, 0, sizeof(tmp_header));
            break;
        }

        else
            memset(tmp_header, 0, sizeof(tmp_header));

        if (errno == EAGAIN || errno == EINTR || errno == EWOULDBLOCK)
        {
            memset(tmp_header, 0, sizeof(tmp_header));
            break;
        }
    }

    printf("buf => %s\n", buf);

    /* telnet error. */
    if (strlen(buf) < 6 or buf == ""){
        return "None";
    }


    /* get client ip. */
    getpeername(remotefd, (struct sockaddr *)&remotetmp, &len);
    char * remoteip = inet_ntoa(remotetmp.sin_addr);

    /* all user input transport to http judge. */
    httpdoing.judgehttpinput(buf);
   
    /* get all user input for correct. */
    std::map<int, std::string> content_length_size = httpdoing.getVar(buf); 
    if (content_length_size[0] == "No")
    {
        usleep(2000);
        if (content_length_size[1] != "None")
        {
    	    int post_body_size = (atoi(content_length_size[1].c_str()));
            char *sure_post;
      	    sure_post = (char*)malloc(sizeof(char) * (post_body_size+1) );
            memset(sure_post, 0, post_body_size+1);
            for(;;)
       	    {
    	        int lengths = read(remotefd, sure_post, post_body_size);
      	        if (lengths > 0)
                {
                    usleep(10);
                    {
                        memcpy(buf+offset, sure_post, post_body_size);
                        offset += post_body_size;
                    }
                }
                else
                {
                    memset(sure_post, 0, sizeof(char) * (post_body_size+1));
                    break;
                }
    	    }
       	    free(sure_post);
        }
    }
    /* White list judge. */
    //bool whitejudge = httpdoing.WhiteList(remoteip);


    /* analyst data. */
    returnbuf = httpdoing.logicPart(true);

    free(tmp_header);


    return returnbuf;
}

/*
This method used to write remote data
need 1 variables : remote file handler
and return non block data.
*/
void XPSOCKET::WriteData(int remotefd, const std::string & data)
{

    const void *tmp = (const void *)(data.c_str());

    char d[data.size()];
    memcpy(d, tmp, data.size());

    int nwrite, data_size = data.size();
    int n = data_size;
    while (n > 0) {
        nwrite = write(remotefd, d + data_size - n, n);
        if (nwrite < n) {
            if (nwrite == -1 && errno != EAGAIN) {
                perror("write error");
            }
            break;
        }
        n -= nwrite;
    }

}

/*
block send data using by block status;
need 2 variables
1. remote file handler
4. flags
*/
void XPSOCKET::SendData(int remotefd, int flags)
{

    int sendage = send(remotefd, "Hello, connection.", 19, flags);

    if (sendage == -1)
    {
        perror("[XPSOCKET::WriteData] Send data error.\n");
    }

}

int * XPSOCKET::getserverfd()
{
    return &_isock;
}
