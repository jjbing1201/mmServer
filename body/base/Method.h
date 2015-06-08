#ifndef _METHOD_PROCESS_HEADHER_H_
#define _METHOD_PROCESS_HEADHER_H_ 

#include <stdio.h>

class METHOD
{
public:
    METHOD(bool _check=true, bool _operation =true, \
            bool _serverreturn =true, bool _format=true) : \
            has_check(_check), \
            has_operation(_operation), \
            has_serverreturn(_serverreturn), \
            has_format(_format) {}
    virtual ~METHOD() {}
    
    /* <<< change status about method. >>> */
    void change_has_check(bool change_check) 
    { has_check = change_check; }
    void change_has_operation(bool change_operation) 
    { has_operation = change_operation; }
    void change_has_serverreturn(bool change_serverreturn) 
    { has_serverreturn = change_serverreturn; }
    void change_has_format(bool change_format) 
    { has_format = change_format; }
    
    /* <<< get status of method. >>> */
    bool get_has_check(void) { return has_check; }
    bool get_has_operation(void) { return has_operation; }
    bool get_has_serverreturn(void) { return has_serverreturn; }
    bool get_has_format(void) { return has_format; }

private:
    bool has_check;
    bool has_operation;
    bool has_serverreturn;
    bool has_format;
};

#endif /* _METHOD_PROCESS_HEADHER_H_ */

