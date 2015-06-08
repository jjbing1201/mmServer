#ifndef _XPEPOLL_HEADER_
#define _XPEPOLL_HEADER_

#include <iostream>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/epoll.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <errno.h>
#include <vector>
#include <sstream>
#include <assert.h>

#include "SingleTon.h"

class TC_Epoller
{
private:
    int _iEpollfd;                  // epoll pool
    int _max_connections;           // max connection number
    struct epoll_event *_pevs;      // all events here
    bool _et;                       // ET or LT
protected:
    void ctrl(int fd, long long data, __uint32_t events, int op);
public:

    TC_Epoller(bool bEt = true); //bEt : true : ET
                                  //bEt : false : LT       
    ~TC_Epoller();

    void create(int max_connections);
    /* wait time. */
    int wait(int millsecond);
    /* get events. */
    struct epoll_event& get(int i) { return _pevs[i]; }
    /* events operation */ 
    void add(int fd, long long data, __uint32_t event);
    void mod(int fd, long long data, __uint32_t event);
    void del(int fd, long long data, __uint32_t event);
};

#endif

typedef SINGLETON<TC_Epoller> newepoll;
