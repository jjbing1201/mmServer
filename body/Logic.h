#ifndef _LOGIC_ANALYST_HEADHER_H_
#define _LOGIC_ANALYST_HEADHER_H_

#include <iostream>
#include <map>
#include <string.h>

#include "body_include.h"

#include "world/Main.h"

#include "database/interfaceusing.h"

class LOGIC
{
private:
    bool whiteauth;

protected:
    /* check user input. */
    std::map<std::string, std::string> postAnalyst(const std::string & data);
    /* record interface using. */
    bool interface_using(std::string get_interface_name);

/*--- check user input Part ---*/
public:
    LOGIC(bool Auth);
    virtual ~LOGIC();
    bool FirstAuth_WhiteList();                                     /* first auth of white list. */
    bool getMethodcheck(const std::string & method, int length);    /* check get method. */
    int dataPutJudge(const std::string & method);                   /* check user put data. */
    std::map<std::string, std::string> analystUrlMethod(std::string & urlmethod);               /* used to analyst POST urlmethod and return. */
    std::string getPostVerifty(const std::string & userinput);      /* method used to get post verifty by user input. */
    std::string getExInput(const std::string & userinput);          /* get user ex input. */
    std::map<std::string, std::string> getCorrectData(const std::string & data, const std::string & verifty); /* get correct of data. */

/*--- decide url method. ---*/
public:
    std::map<std::string, std::string> getAccessMethod(const std::string & urlmethod);     /* through method get Access Method from ini file. */

    std::map<std::string, std::string> DoingInputVariable(std::map<std::string, std::string> getAccessReturn, std::map<std::string, std::string> data);   /* through method test input variable. */

/*--- combine result data. ---*/
public:
    /* part of header. */
    std::map<std::string, std::string> headerPart(std::string status);          

    /* part of body. */
    std::string bodyPart(std::string status, std::string & header);

    /* part of body. */
    std::string bodyPart(std::string status, std::string & header, std::string & body);

    /* part of help body*/
    std::string helpbodyPart(const std::string & headOne, const std::string & headTwo, const std::string & body); 

};
#endif /* _LOGIC_ANALYST_HEADHER_H_ */

