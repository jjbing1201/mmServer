#include "sms.h"

ssize_t http_post(char *page, char *poststr)
{
    char sendline[MAXLINE + 1], recvline[MAXLINE + 1];
    ssize_t n;
    snprintf(sendline, MAXSUB,
             "POST %s HTTP/1.0\r\n"
             "Host: %s\r\n"
             "Content-type: application/x-www-form-urlencoded\r\n"
             "Content-length: %zu\r\n\r\n"
             "%s", page, hname, strlen(poststr), poststr);

    write(sockfd, sendline, strlen(sendline));
    while ((n = read(sockfd, recvline, MAXLINE)) > 0) {
        recvline[n] = '\0';
        printf("%s", recvline);
    }
    return n;
}

/**
 * 使用通用接口发短信
 */
ssize_t send_sms(char *apikey, char *mobile, char *text)
{
    char params[MAXPARAM + 1];
    char *cp = params;
    sprintf(cp,"apikey=%s&mobile=%s&text=%s", apikey, mobile, text);
    return http_post(send_sms_json, cp);
}

int send_sms_interface(char* cellphone, char* text)
{
    struct sockaddr_in servaddr;
    char **pptr;
    char str[50];
    struct hostent *hptr;
    if ((hptr = gethostbyname(hname)) == NULL) {
        fprintf(stderr, "通过域名获取IP失败: %s: %s",
                hname, hstrerror(h_errno));
        exit(1);
    }
    printf("域名: %s\n", hptr->h_name);
    if (hptr->h_addrtype == AF_INET
        && (pptr = hptr->h_addr_list) != NULL) {
        printf("IP: %s\n",
               inet_ntop(hptr->h_addrtype, *pptr, str,
                         sizeof(str)));
    } else {
        fprintf(stderr, "Error call inet_ntop \n");
        exit(1);
    }

    //建立socket连接
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(80);
    inet_pton(AF_INET, str, &servaddr.sin_addr);

    connect(sockfd, (SA *) & servaddr, sizeof(servaddr));

    //修改为您的apikey
    char *apikey = "845068b98391628e22fe6c2c25207c94";

    send_sms(apikey, cellphone, text);

    close(sockfd);

    return 0;
}
