#ifndef _XP_CURL_HEADER_H_
#define _XP_CURL_HEADER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

class XPCURL
{
private:
    CURL *curl;         // libcurl inside element
    CURLcode res;       // libcurl resource return

    char *get_string;   // get return result

protected:
    /*
     * \brief : this method used post method to get
     *          combine of url to record server
     * \param : char * => url store
     *          char * => ipaddress
     *          chat * => port
     * \return : -1 for error, 0 for ok.
    */
    int url_combine(char* , char*, char*); 

    /*
     * \brief : this method used post method to get
     *          visit url
     * \param : char * => return result
     *          char * => visit url
     *          char * => visit param
     *          int => timeout
     * \return : -1 for error, 0 for ok. 
    */ 
    int visit_url(char *, char *, char *, int);

    /*
     * \brief : visit url for sms protected method
    */
    int visit_url_get(char *, char *, int); 

public:
    XPCURL();
    virtual ~XPCURL();

    /*
     * \brief : this method used post method to get
     *          url's return data
     * \param : char * => out data
     *          char * => post method
     *          char * => post data
     * \return : NULL for error, other for ok.
    */
    int post_url_method(char*, char*, char*); 

    /*
     * \brief : post data to sms server for only
    */
    int post_whole_url_method(char*, char*, char*);

    /*
     * \brief : post data to any url 
    */
    int post_whole_url_method(char*, char*, char*, char*);
};

#endif /* _XP_CURL_HEADER_H_ */

