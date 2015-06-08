#ifndef _CHARSET_HEADER_H_
#define _CHARSET_HEADER_H_

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <iconv.h>

class CODECONVERT
{
public:
    CODECONVERT();
    ~CODECONVERT();

    /*
     * \brief   : in => input char context
     *          : out => output char context
     *          : out_size => output char length
     *          : tocode => destination charset
     *          : fromcode => source charset
     * \result  : method will give user define of tocode and fromcode for user
     * \return  : -1 for error, 0 for success
    */
    int charConvert(unsigned char *in, unsigned char *out, size_t out_size, const char &tocode, const char &fromcode);

    /*
     * \brief   : in => input char context
     *          : out => output char context
     *          : out_size => output char length
     * \result  : method will give user define of utf8 code to gb2312 for user
     * \return  : -1 for error, 0 for success
    */
    int utf8togb2312(unsigned char *in, unsigned char *out, size_t out_size);

    /*
     * \brief   : in => input char context
     *          : out => output char context
     *          : out_size => output char length
     * \result  : method will give user define of gb2312 to utf8 for user
     * \return  : -1 for error, 0 for success 
    */ 
    int gb2312toutf8(unsigned char *in, unsigned char *out, size_t out_size);

    int utf8tocp936(unsigned char *in, unsigned char *out, size_t out_size);
};

#endif /* _CHARSET_HEADER_H_ */

