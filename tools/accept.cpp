#include "accept.h"

void* ACCEPT_THREAD::run(void* param)
{
    int fd = atoi((char*)param);

    std::string reData = newsocket::GetInstance().ReadData(newepoll::GetInstance().get(fd).data.fd);

    newsocket::GetInstance().WriteData(newepoll::GetInstance().get(fd).data.fd, reData);

    newepoll::GetInstance().del(newepoll::GetInstance().get(fd).data.fd, 0, EPOLLOUT);

    return param;
}
