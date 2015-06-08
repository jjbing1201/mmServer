#ifndef _BASIC_ALGORITHM_HEADER_
#define _BASIC_ALGORITHM_HEADER_

#include <iostream>
#include <string.h>
#include <zlib.h>

#include "include_unit.h"

class BASICALG
{
private:
    std::string base64_chars;
    static inline bool is_base64(unsigned char c)
    {
        return (isalnum(c) || (c == '+') || (c == '/'));
    };

    /* url encode strong. */
    std::string char2hex(char dec);

public:
    BASICALG();
    virtual ~BASICALG();

    /* --- URL CODE --- */
    std::string UrlEncode(const std::string &);
     /* url encode method. */
    std::string UrlDecode(const std::string &);
     /* url decode method. */

    std::string Strong_UrlEncode(const std::string & c);
     /* strong url encode -> like python quote_plus */

    /* --- Base64 ---*/
    std::string base64_encode(unsigned char const* , unsigned int len);
     /* base64 encode. */
    std::string base64_decode(std::string const&);
     /* base64 decode. */

    /* --- Zlib --- */
    std::string zlib_encode(const char *);
     /* zlib encode. */
    std::string zlib_decode(char *);
     /* zlib decode. */
};

#endif /* _BASIC_ALGORITHM_HEADER_ */
