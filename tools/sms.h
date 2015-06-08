#ifndef _SMS_OF_MESSAGESERVER_HEADER_
#define _SMS_OF_MESSAGESERVER_HEADER_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "include_tools.h"

#include "../framework/XPcurl.h"

class MESSAGE_SMS
{
private:
    char *apiKey;

    char *sure_data;    // before send will check data format

    char *return_data;  // after send will check data content

    char *url_method;   // url of platform

    char *url_data;     // url of platform data

protected:
    int check_telephone(char *);

    int check_data(char *);

    int sms_url_method_combine();   // create sms url method

    int data_combine(char *, char *);       // real data

public:
    MESSAGE_SMS();
    virtual ~MESSAGE_SMS();

    int push_notification_of_sms(char *, char *);
};

#endif /* _SMS_OF_MESSAGESERVER_HEADER_ */

