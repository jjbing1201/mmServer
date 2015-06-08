#include "sms.h"

MESSAGE_SMS::MESSAGE_SMS()
{
    apiKey = "845068b98391628e22fe6c2c25207c94";
    sure_data = (char *)malloc(sizeof(char)*SMS_LENGTH);
    return_data = (char *)malloc(sizeof(char)*SMS_RETURN_LENGTH);
    url_method = (char *)malloc(sizeof(char)*256);
    url_data = (char *)malloc(sizeof(char)*SMS_CONTENT);
}

MESSAGE_SMS::~MESSAGE_SMS()
{
    free(url_data);
    free(url_method);
    free(return_data);
    free(sure_data);
}

int MESSAGE_SMS::check_telephone(char * _telephone)
{
    return strlen(_telephone) == 11 ? 0 : -1;
}

int MESSAGE_SMS::check_data(char * _data)
{
    memset(sure_data, 0, sizeof(char)*SMS_LENGTH);

    if ((strlen(_data)) > SMS_LENGTH)
    {
        memcpy(sure_data, _data, SMS_LENGTH-1);
    }
    else
    {
        memcpy(sure_data, _data, strlen(_data));
    }

    return 0;
}

int MESSAGE_SMS::sms_url_method_combine()
{
    int count=0;
    memset(url_method, 0, 256);

    // host
    char sms_host[16];
    memset(sms_host, 0, 16);    
    memcpy(sms_host, "www.yunpian.com", strlen("www.yunpian.com"));

    // port
    char sms_port[6];
    memset(sms_port, 0, 6); 
    memcpy(sms_port, "80", strlen("80"));

    // method
    std::string sms_method = "v1/sms/send.json";

    // all combine -> http://192.168.100.5:19997/emaysendMsg
    memcpy(url_method+count, "http://", strlen("http://"));
    count += strlen("http://");

    memcpy(url_method+count, sms_host, strlen(sms_host));
    count += strlen(sms_host);

    memcpy(url_method+count, ":", strlen(":"));
    count += strlen(":");

    memcpy(url_method+count, sms_port, strlen(sms_port));
    count += strlen(sms_port);

    memcpy(url_method+count, "/", strlen("/"));
    count += strlen("/");

    memcpy(url_method+count, sms_method.c_str(), strlen(sms_method.c_str()));
    count += strlen(sms_method.c_str());

    return count;
}

int MESSAGE_SMS::data_combine(char * _input_telephone, char * data)
{
    /* out side url decode using */
    BASICALG alg;
    CODECONVERT codeconvert;

    int count=0;
    /* get host and port from ini file. */
    memset(url_data, 0, SMS_CONTENT);

    // -> apikey=845068b98391628e22fe6c2c25207c94&mobile=10086100861&text=1234
    memcpy(url_data+count, "apikey=", strlen("apikey="));
    count += strlen("apikey=");
    
    memcpy(url_data+count, apiKey, strlen(apiKey));
    count += strlen(apiKey);

    memcpy(url_data+count, "&mobile=", strlen("&mobile="));
    count += strlen("&mobile=");

    memcpy(url_data+count, _input_telephone, strlen(_input_telephone));
    count += strlen(_input_telephone);

    memcpy(url_data+count, "&text=", strlen("&text="));
    count += strlen("&text=");
    
    char *gb2312_data;
    gb2312_data = (char*)malloc(sizeof(char)*strlen(data)*2);
    memset(gb2312_data, 0, strlen(data)*2);
    codeconvert.utf8togb2312((unsigned char *)data, (unsigned char *)gb2312_data, strlen(data)*2);
    std::string _gb2312_data = gb2312_data;  
    std::string urlcode_after_data = alg.Strong_UrlEncode(_gb2312_data);
    free(gb2312_data);

    memcpy(url_data+count, (char*)urlcode_after_data.c_str(), strlen((char*)urlcode_after_data.c_str()));
    count += strlen((char*)urlcode_after_data.c_str());

    return count;
}

int MESSAGE_SMS::push_notification_of_sms(char * telephone, char * data)
{
    /* statement */
    XPCURL xpcurl;

    /* check data sure */
    char get_input_data[256+SMS_CONTENT];
    memset(get_input_data, 0, 256+SMS_CONTENT);

    if (check_telephone(telephone) != 0)
    {
        return -1;
    }
    if (check_data(data) != 0)
    {
        return -1;
    }

    // get url method
    if ( (sms_url_method_combine()) == 0)
    {
        return -1;
    }

    if ( (data_combine(telephone, sure_data)) == 0)
    {
        return -1;
    }

    /* real send operation */
    memcpy(get_input_data, url_method, strlen(url_method));
    memcpy(get_input_data+strlen(url_method), "?", strlen("?"));
    memcpy(get_input_data+strlen(url_method)+strlen("?"), url_data, strlen(url_data));

    memset(return_data, 0, SMS_RETURN_LENGTH);

    //int return_xpcurl_result = xpcurl.post_whole_url_method(return_data, get_input_data, "2"); 
    int return_xpcurl_result = xpcurl.post_whole_url_method(return_data, "yunpian.com", "v1/sms/send.json", url_data); 

    return return_xpcurl_result;
}
