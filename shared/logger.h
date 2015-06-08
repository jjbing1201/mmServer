#ifndef _LOGGER_HEADER_H_
#define _LOGGER_HEADER_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../framework/SingleTon.h"

class LOGGER
{
private:
    std::string initlevel; // logger init level
    std::string outputdir; // logger output dir path
    std::string outputfile; // logger output file path.
    std::vector<std::string> loggerlevel;  // logger level list

protected:
    std::string inttostr(int integer); // from integer to string
    std::string nowfilename(void); // get now filename of loggerfile.
    std::string format_context(const std::string &servername, const std::string &loglevel, std::string data); // format logger input;
    std::string format_context(const std::string &servername, const std::string &loglevel, std::string title, std::string data); // format logger input with title;

public:
    LOGGER();
    ~LOGGER();

    /* 
     * @param : loglevel
     * @context : log context 
     * @return : 0 for error , 1 for right.
     * @usage : store information in logger file. 
    */
    int LOG(const std::string &loglevel, std::string context);
    /* 
     * @param : loglevel
     * @param : log title
     * @context : log context 
     * @return : 0 for error , 1 for right.
     * @usage : store information in logger file. 
    */
    int LOG(const std::string &loglevel, std::string logtitle, std::string context);
};

#endif /* _LOGGER_HEADER_H_ */

/* singleton to start */
typedef SINGLETON<LOGGER> logger;
