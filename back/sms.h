#ifndef _SMS_GLOBAL_
#define _SMS_GLOBAL_

#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <unistd.h>

#define SA      struct sockaddr
#define MAXLINE 4096
#define MAXSUB  2000
#define MAXPARAM 2048

#define LISTENQ         1024

extern int h_errno;

int sockfd;
char *hname = "yunpian.com";
char *send_sms_json = "/v1/sms/send.json";
char *get_user_json = "/v1/user/get.json";

ssize_t http_post(char *page, char *poststr);

/**
 * 使用通用接口发短信
 */
ssize_t send_sms(char *apikey, char *mobile, char *text);

int send_sms_interface(char* cellphone, char* text);

#endif /* _SMS_GLOBAL_ */
