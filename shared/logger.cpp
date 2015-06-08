#include "logger.h"

LOGGER::LOGGER()
{
    struct stat fileStat;

    /* 1. get default logger set. */
    initlevel = "NOSET";

    /* 2. get default logger name. */
    outputfile = "Server";

    /* 3. get default logger dir name. */
    outputdir = "/tmp/server/";
    if ((stat(outputdir.c_str(), &fileStat) == 0) && S_ISDIR(fileStat.st_mode))
    {
    
    }else{ 
        int create_dir = mkdir(outputdir.c_str(), 0755);
    }

    /* 4. input get level list. */
    loggerlevel.push_back("NOSET");
    loggerlevel.push_back("DEBUG");
    loggerlevel.push_back("INFO");
    loggerlevel.push_back("WARNING");
    loggerlevel.push_back("ERROR");
    loggerlevel.push_back("FATAL");
    
}

LOGGER::~LOGGER()
{
    //std::string *pointer = loggerlevel.get_allocator().allocate(6);
    //loggerlevel.get_allocator().deallocate(pointer, 6);
}

std::string LOGGER::inttostr(int integer)
{
    std::stringstream mid;
    std::string result;
    mid << integer;
    mid >> result;

    if (result.length() < 2)
    {
        result = "0"+result;
    }

    return result;
}
std::string LOGGER::nowfilename(void)
{
    /* 1. define return result. */
    std::string result;

    /* 2. get now time. 
     * year = tm_year+1900
     * month = tm_mon + 1
     * day = tm_mday
     * hour = tm_hour
     * min = tm_min
     * sec = tm_sec
    */
    time_t rawtime;
    struct tm *ptm;
    time(&rawtime);
    ptm = gmtime(&rawtime);

    /* 3. change integer to string and combine. */
    std::string get_year = inttostr((ptm->tm_year+1900));
    std::string get_mon = inttostr((ptm->tm_mon+1));
    std::string get_day = inttostr((ptm->tm_mday));
    std::string get_hour = inttostr((ptm->tm_hour+8)); // +8 time zone area. 

    std::string timenow = get_year+get_mon+get_day+"-"+get_hour;

    result = outputdir+outputfile+"."+timenow;

    return result; 
}

std::string LOGGER::format_context(const std::string &servername, const std::string &loglevel, std::string data)
{
    /* 1. statement return cmd. */
    std::string result;

    /* 2. get pid. */
    pid_t processid = getpid();

    /* 3. timestamp. */
    time_t timeheap;
    time(&timeheap);
    std::string timeuse = asctime(gmtime(&timeheap));

    /* 4. combine result */
    result += timeuse.substr(0, timeuse.length()-1);
    result += " ["+inttostr(processid)+"] ";
    result += servername+" ";
    result += "<"+loglevel+"> : ";
    result += data+"\n";

    return result;
}

std::string LOGGER::format_context(const std::string &servername, const std::string &loglevel, \
                                    std::string title, std::string data)
{
    /* 1. statement return cmd. */
    std::string result;

    /* 2. get pid. */
    pid_t processid = getpid();

    /* 3. timestamp. */
    time_t timeheap;
    time(&timeheap);
    std::string timeuse = asctime(gmtime(&timeheap));

    /* 4. combine result */
    result += timeuse.substr(0, timeuse.length()-1);
    result += " ["+inttostr(processid)+"] ";
    result += servername+" ";
    result += "<"+loglevel+"> : ";
    result += "***"+title+"***: ";
    result += data+"\n";

    return result;
}


int LOGGER::LOG(const std::string &loglevel, std::string context)
{
    /* 1. check loglevel in loggerlevel vector. */
    int i;
    int now;
    int initnum;
    int logcorrect=0;
    for (i=0; i<loggerlevel.size(); i++)
    {
        if (loglevel == loggerlevel[i])
        {
            now = i;
            logcorrect=1;
        }
        else if(initlevel == loggerlevel[i])
        {
            initnum = i;
        }
    } 
    if (logcorrect == 0)
    {
        return logcorrect;
    }


    /* 2. get sure about input file path. */
    std::string nowfile = nowfilename();
    
    /* 3. judge file exist and could be write into. */
    int check_exist = access(nowfile.c_str(), 00);
    if (check_exist == -1)
    {
        // 0100 -> O_CREAT define in fcntl.h
        int newcreate = creat(nowfile.c_str(), 0640);
    }
    
    int check_writein = access(nowfile.c_str(), 02);
    if (check_writein == -1)
    {
        return 0;
    }
    
    /* 4. input log level > init level */
    if (initnum <= now)
    {
        /* 5. write data combine. */
        std::string formatre = format_context("mmog", loglevel, context);
        std::ofstream directfile;
        directfile.open(nowfile.c_str(), std::ios::out|std::ios::app);
        if (directfile.is_open())
        {
            directfile << formatre;
            directfile.close();
        }else{
            return 0;
        }

    }

    else{
        return 0;
    }
    
    return 1;
} 

int LOGGER::LOG(const std::string &loglevel, std::string logtitle, std::string context)
{
    /* 1. check loglevel in loggerlevel vector. */
    int i;
    int now;
    int initnum;
    int logcorrect=0;
    for (i=0; i<loggerlevel.size(); i++)
    {
        if (loglevel == loggerlevel[i])
        {
            now = i;
            logcorrect=1;
        }
        else if(initlevel == loggerlevel[i])
        {
            initnum = i;
        }
    }  
    if (logcorrect == 0)
    { 
        return logcorrect;
    } 
 
 
    /* 2. get sure about input file path. */
    std::string nowfile = nowfilename();
     
    /* 3. judge file exist and could be write into. */
    int check_exist = access(nowfile.c_str(), 00);
    if (check_exist == -1)
    { 
        // 0100 -> O_CREAT define in fcntl.h
        int newcreate = creat(nowfile.c_str(), 0640);
    } 
     
    int check_writein = access(nowfile.c_str(), 02);
    if (check_writein == -1)
    { 
        return 0;
    } 
     
    /* 4. input log level > init level */
    if (initnum <= now)
    { 
        /* 5. write data combine. */
        std::string formatre = format_context("mmog", loglevel, logtitle, context);
        std::ofstream directfile;
        directfile.open(nowfile.c_str(), std::ios::out|std::ios::app);
        if (directfile.is_open())
        {
            directfile << formatre;
            directfile.close();
        }else{
            return 0;
        }
 
    } 

    else{
        return 0;
    }

    return 1;
}
