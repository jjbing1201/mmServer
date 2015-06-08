#include <stdio.h>
#include <map>
#include <vector>
#include <time.h>
#include <string.h>

#include "../shared/md5.h"
#include "../shared/util.h"
#include "../shared/gerror.h"
#include "../shared/logger.h"
#include "../shared/basicalgorithm.h"

#include "../config/iniexpand.h"

#include "../body/Logic.h"

class HttpAction
{
private:
    int _inputlength;            /* user input data length. */
    std::string _userMethod;     /* used to store user input : get or post. */
    std::string _remotehost;     /* remote host ipaddress. */
    std::string _inputdata;      /* user input data detail. */
    std::string _urlmethod;      /* user input method. */
    std::map<std::string, std::string> _variable; /* map to save variable. */ 
    enum { TOKEN_LENGTH = 25 };  /* token length. */
    char token[TOKEN_LENGTH]; 
    int nowtime;                 /* now timestamp. */
    timespec overtime;           /* link overtime. */
public:
    HttpAction();
    ~HttpAction();
    int getNowtime();                       /* get system current timestamp. */
    bool WhiteList(const char * remoteip);  /* check judge whitelist exist. */
    std::string getToken();                 /* method to get token. char -> string */
    void createTokenOvertime();             /* create link token and overtime. */
    std::map<int, std::string> getVar(const char * buf);          /* get all data from package. */
    void judgehttpinput(const char * buf);  /* judge user input data. */
public:
    std::string logicPart(bool whiteAuth);         /* part of logic call. */
};
