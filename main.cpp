#include <iostream>
#include <stdlib.h>
#include <unistd.h>

#include "framework/XPepoll.h"
#include "framework/XPsocket.h"
#include "framework/XPmysql.h"
#include "framework/XPmysqlmessage.h"
#include "framework/XPmysqlholter.h"

#include "tools/active.h"
#include "tools/accept.h"
#include "shared/gtimer.h"
#include "config/iniexpand.h"

void action_function(int)
{
    ACTIVE_OP active_op;
    active_op.ac_start();
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        std::string daemonbg = "-d";
        if (argv[1] == daemonbg)
        {
            daemon(1, 0);
        }
    }

/* ------------------- */
    GTIMER gtimer;
    gtimer.set_timer(10, 86400*1);
    signal(SIGALRM, action_function);

/* ------------------- */

    int conn_sock;
    int waitsecond = 1000;
    std::string ipaddress = "0.0.0.0";
    const void *ip = (const void *)(ipaddress.c_str());
    int port = 10000;

    /* global statement. */
    INIReader reader("../config.ini");
    
    std::string connect = reader.Get("DATABASE","1.master","None");
    std::string connectmsg = reader.Get("DATABASE","2.master","None");

    std::map<std::string, std::string> connectdetail = datacon::GetInstance().dbconnectInfo(connect);
    std::map<std::string, std::string> connectdetailmsg = messagecon::GetInstance().dbconnectInfo(connectmsg);

    datacon::GetInstance().create_connect(connectdetail["ipaddress"], atoi(connectdetail["port"].c_str()), connectdetail["username"], connectdetail["password"], connectdetail["dbname"]);
    messagecon::GetInstance().create_connect(connectdetailmsg["ipaddress"], atoi(connectdetailmsg["port"].c_str()), connectdetailmsg["username"], connectdetailmsg["password"], connectdetailmsg["dbname"]);

    /* create socket. */
    newsocket::GetInstance().Create(SOCK_STREAM, AF_INET, 0);

    /* set socket with non block. */
    newsocket::GetInstance().Setnonblock();

    /* set socket ipaddr and port. */
    newsocket::GetInstance().InitSocket(ip, port, ipaddress.size());

    /* bind socket. */
    newsocket::GetInstance().Bindsocket();

    /* listen socket. */
    newsocket::GetInstance().Listensocket();

    /* create epoll. */
    newepoll::GetInstance().create(1000);

    /* add server fd into epfd. */
    int *serverfd = newsocket::GetInstance().getserverfd();
    newepoll::GetInstance().add(*serverfd, 0, EPOLLIN);

    for (;;)
    {
        int waits = newepoll::GetInstance().wait(waitsecond);

        if ((datacon::GetInstance().test_connect()) < 0)
            datacon::GetInstance().create_connect(connectdetail["ipaddress"], atoi(connectdetail["port"].c_str()), connectdetail["username"], connectdetail["password"], connectdetail["dbname"]);

	if ((messagecon::GetInstance().test_connect()) < 0)
	    messagecon::GetInstance().create_connect(connectdetailmsg["ipaddress"], atoi(connectdetailmsg["port"].c_str()), connectdetailmsg["username"], connectdetailmsg["password"], connectdetailmsg["dbname"]);

        for (int i=0; i < waits; ++i)
        {
            int fd = newepoll::GetInstance().get(i).data.fd;
            if (fd == *serverfd)
            {
                while((conn_sock=newsocket::GetInstance().Acceptlink()) > 0)
                {
                    newsocket::GetInstance().Setnonblock(conn_sock);
                    newepoll::GetInstance().add(conn_sock, 0, EPOLLIN);
                }
                if (conn_sock == -1) {
                    if (errno != EAGAIN && errno != ECONNABORTED && errno != EPROTO && errno != EINTR)
                        perror("accept error.\n");
                }
                continue;
            }

            if (newepoll::GetInstance().get(i).events & EPOLLIN)
	    {
                char each_fd[6];
                memset(each_fd, 0, 6);
                sprintf(each_fd, "%d", i);

                // add into accept thread and wait will be send fd to out.
                ACCEPT_THREAD e;
                e.start(false, (void*)each_fd, SCHED_RR, false);
                (char*)e.wait(); 
            }

            if (newepoll::GetInstance().get(i).events & EPOLLOUT)
            {
                close(newepoll::GetInstance().get(i).data.fd);
            }
        }
    }

    
    return 0; 
}
