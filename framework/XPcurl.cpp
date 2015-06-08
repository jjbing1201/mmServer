#include "XPcurl.h"

static size_t writer(void *p, size_t size, size_t nmemb, void *stream)
{ 
    /*
    if (strlen((char*)stream)+strlen((char*)p) > 2048)
    {
        return 0;
    }
    strcat((char*)stream, (char*)p);
    return size*nmemb;
    */
    
    strcat((char*)stream, (char*)p);
    return size*nmemb;
} 

XPCURL::XPCURL()
{
    curl = curl_easy_init(); 
}

XPCURL::~XPCURL()
{
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

int XPCURL::url_combine(char* c_url, char* _ipaddress, char* _port)
{
    try
    {
        strcpy(c_url, "http://");
        strcat(c_url, _ipaddress);
        strcat(c_url, ":");
        strcat(c_url, _port);
        
        return 0;
    }
    catch(...)
    {
        return -1;
    }
}

int XPCURL::visit_url(char *string, char *v_url, char *params, int timeout)
{ 
    struct curl_slist *headerlist = NULL;
    const char buf[] = "Expect:";
    headerlist = curl_slist_append(headerlist, buf);
    headerlist = curl_slist_append(headerlist, "Content-Type: application/x-www-form-urlencoded; charset=GB2312");

    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1);
    curl_easy_setopt(curl, CURLOPT_URL, v_url); 
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout); 
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params); 
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writer); 
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, string); 
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headerlist);
     
    res = curl_easy_perform(curl); 

    if (CURLE_OK != res) 
    { 
        return -1; 
    } 
    return 0; 
} 

int XPCURL::visit_url_get(char *string, char *v_url, int timeout)
{
    curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
    curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1);
    curl_easy_setopt(curl, CURLOPT_URL, v_url);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);

    res = curl_easy_perform(curl);

    if (CURLE_OK != res)
    {
        return -1;
    }
    return 0;
}

int XPCURL::post_url_method(char *outdata, char* method, char* data)
{
    /* 1. initialized get string. */
    char *record_url;
    record_url = (char*)malloc(sizeof(char)*32);
    memset(record_url, 0, 32);

    /* 2. read from config file to get record server information */
    int timeout = 2;
    char port[6];
    memset(port, 0, 6);
    char recordip[16];
    memset(recordip, 0, 16);

    /* 3. get record server url. */
    int get_recordserver_url_return = url_combine(record_url, recordip, port);
    if (get_recordserver_url_return == -1)
    {
        return -1;
    }

    /* 4. get whole url. */
    char *url;
    url = (char *)malloc(sizeof(char)*128);
    memset(url, 0, 128);
    strcpy(url, record_url);
    strcat(url, "/");
    strcat(url, method);


    /* 5. get return data. */
    int curl_re = visit_url(outdata, url, data, timeout);   
    if (curl_re == -1)
    {
        free(url);
        free(record_url);
        return -1;
    }
    else
    {
        free(url);
        free(record_url);
        return 0;
    }
}

int XPCURL::post_whole_url_method(char *outdata, char *url_plus_data, char *timeout)
{
    /* 1. get return data. */
    int curl_re = visit_url_get(outdata, url_plus_data, atoi(timeout));
    if (curl_re == -1 or curl_re == 0)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int XPCURL::post_whole_url_method(char *outdata, char *url, char* method, char* data)
{

    /* 4. get whole url. */
    char *real_url;
    real_url = (char *)malloc(sizeof(char)*128);
    memset(real_url, 0, 128);
    memcpy(real_url, url, strlen(url));
    memcpy(real_url+strlen(url), "/", strlen("/"));
    memcpy(real_url+strlen(url)+strlen("/"), method, strlen(method));

    /* 5. get return data. */
    int curl_re = visit_url(outdata, real_url, data, 3);
    if (curl_re == -1)
    {
        free(real_url);
        return -1;
    }
    else
    {
        free(real_url);
        return 0;
    }
}
