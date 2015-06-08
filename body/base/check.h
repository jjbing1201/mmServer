#ifndef _CHECK_INPUT_HEADER_H_
#define _CHECK_INPUT_HEADER_H_

#include "include_base.h"

class CHECKDATA
{
public:
    CHECKDATA(int _outside=DEFAULT_CHECK_OUTSIDE, \
              int _inside=DEFAULT_CHECK_INSIDE) : \
        package_outside_check(_outside), \
        package_inside_check(_inside) {}
    virtual ~CHECKDATA() {}

    int* get_check_outside(void) { return &package_outside_check; }
    int* get_check_inside(void) { return &package_inside_check; }

    /* 
     *  @brief  : outside check for data
     *  @detail : method will check first data and get data inside
     *  @return : data["Status"] & data["Info"] 
    */
    std::map<std::string, std::string> normal_check_outside(std::map<std::string, std::string> data);

    /* 
     *  @brief  : inside check for data
     *  @detail : child class will override this method if _inside = true
     *  @return : will decide by data from checkdata child class
    */
    virtual std::map<std::string, std::string> check_inside(std::map<std::string
, std::string> data) = 0;

private:
    int package_outside_check;
    int package_inside_check;
};

#endif /* _CHECK_INPUT_HEADER_H_ */
