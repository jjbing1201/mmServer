#ifndef _UTIL_NORMAL_HEADER_
#define _UTIL_NORMAL_HEADER_

#include <iostream>
#include <map>
#include <vector>
#include <sstream>

#include "include_unit.h"

/* <<< rand part. >>>*/
int32 irand(int32 min, int32 max);
uint32 urand(uint32 min, uint32 max);
float frand(float min, float max);
int pointrand(int q, int max);

/* <<< timestamp >>> */
uint32 nowtimestamp(void);
std::string format_from_time(int);
std::string format_to_time(char*, int);

/* <<< split >>> */
std::vector<std::string> split(const std::string&, std::string);

/* <<< anything to string. >>> */
template <typename T>
std::string anytostr(const T any)
{
    std::stringstream mid;
    std::string result;
    mid << any;
    mid >> result;

    return result;
}

/* <<< judge ipaddress. >>> */
bool isIpaddress(char *);

/* <<< execute command. >>> */
void executeCMD(const char *, char *);

/* <<< create pid file. >>> */
uint32 CreatePIDFile(const std::string&);

/* <<< charset. >>> */
int utf8togb2312(unsigned char*, unsigned char*, size_t);
int convert(char*, int, char*, int, const char*, const char *);

/* <<< explain json >>> */
std::map<std::string, std::string> json_to_pair(std::string);

#endif /* _UTIL_NORMAL_HEADER_ */

