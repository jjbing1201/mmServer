#include "XPhttp.h"

HttpAction::HttpAction()
{
    _userMethod = "";
    _remotehost = "";
    _inputlength = 0;
    _inputdata = "";
    _urlmethod = "";
    overtime.tv_sec = 300;
}

HttpAction::~HttpAction()
{
    _userMethod = "";
    _remotehost = "";
    _inputlength = 0;
    _inputdata = "";
    _urlmethod = "";
}

void HttpAction::judgehttpinput(const char * buf)
{
    // buf -> all user input 
    int gets = strspn(buf, "GET");  // get judge
    int getp = strspn(buf, "POST"); // post judge

    _userMethod = gets > getp ? "GET" : "POST";
}

std::map<int, std::string> HttpAction::getVar(const char * buf)
{
    std::map<int, std::string> result;

    /* split all information by line. */
    std::vector<std::string> lineVector = split(buf, "\n");
    
    for (int each=0; each < lineVector.size(); ++each)
    {
        if ((lineVector[each].find("Host")) != std::string::npos)
        {
            _remotehost = lineVector[each].substr(6);
            std::string::size_type position = _remotehost.find(":");
            if (position != std::string::npos)
            {
                _remotehost = _remotehost.substr(0, position);    
            }else{
                _remotehost = _remotehost;
            }
        }
    }

    /* get first line. */
    std::vector<std::string> firstlineVector = split(lineVector[0], " ");
    if (_userMethod == "GET")
    {
        int location = firstlineVector[1].find("?");
        if (location > 0)
        {
            _urlmethod = firstlineVector[1].substr(0, location);
            _inputdata = firstlineVector[1].substr(location + 1);
            _inputlength = _inputdata.size();
        }else{
            _urlmethod = firstlineVector[1];
            _inputdata = "";
            _inputlength = 0;
        }        
    }else if(_userMethod == "POST"){
        _urlmethod = firstlineVector[1];
        _inputdata = lineVector.back();
	if (_inputdata.find("auth") != std::string::npos)
            _inputlength = strlen(_inputdata.c_str());
	else
	    goto search_accept_again;
    }

    /* define different variable. */
    if (_inputlength > 0)
    {
        std::vector<std::string> varsplit = split(_inputdata, "&");

        for (int tmpvar = 0; tmpvar < varsplit.size(); tmpvar++)
        {
            int findeq = varsplit[tmpvar].find("=");
            std::string name = varsplit[tmpvar].substr(0, findeq);
            std::string value = varsplit[tmpvar].substr(findeq+1);
            
            _variable[name] = value;
        }
    }

    result[0] = "Yes";
    result[1] = anytostr(_inputlength);
    return result;

search_accept_again:
    unsigned int i;
    std::string post_length = "None";
    for (i=0; i<lineVector.size(); ++i)
    {
	if ((lineVector[i].find("Content-Length: ")) != std::string::npos)
        {
	    std::string::size_type positions = lineVector[i].find("Content-Length: ");
	    post_length = lineVector[i].substr(positions, lineVector[i].size());
	}
    }
    result[0] = "No";
    result[1] = post_length;    
    return result;
}

bool HttpAction::WhiteList(const char * remoteip)
{
    /* Statement ini reader. */
    INIReader reader("../config.ini");

    bool result = false;
    
    /* judge could be read. */
    if (reader.ParseError() < 0)
    {
        printf("can't read config.ini.\n");
        return false;
    }

    /* get each of white list data. 
       Max line = 3 */    
    for (int i=0; i<=3; i++)
    {
        std::string tmpcount = anytostr(i);
        std::string tmp = reader.Get("WHITELIST",tmpcount.c_str(),"None");
        if (tmp != "None")
        {
            if (tmp == remoteip)
            {
                result = true;
            }
        }
    }
    return result;
}

void HttpAction::createTokenOvertime()
{
    /* Statement. */
    MD5 md5(_inputdata); 
    BASICALG basicalgorithm;

    /* calc md5. */
    std::string md5calc = md5.md5();

    /* calc base64. */
    const unsigned char *newbase = (const unsigned char *)(_inputdata.c_str());
    std::string base64calc = basicalgorithm.base64_encode(newbase, _inputlength);

    /* create token rule :  
       16 bit : md5 (from begin to end)
       8 bit : base64 (from begin to end) 
    */
    memset(token, 0, TOKEN_LENGTH); // initialize token buf

    /* first into md5. */
    strncpy(token, md5calc.c_str(), 16); 
    /* second into base64. */
    strncat(token, base64calc.c_str(), 8);
}

std::string HttpAction::getToken()
{
    std::string tmpGettoken;
    tmpGettoken = token;
    return tmpGettoken;
}

/*
This method used to get system current timestamp.
and return.
*/
int HttpAction::getNowtime()
{
    time_t tmptime;
    time(&tmptime);
    nowtime = tmptime; /* give result store. */

    return tmptime;
}


/* public part logic call. */
std::string HttpAction::logicPart(bool whiteAuth)
{
    std::map<std::string, std::string> header;
    std::string body;
    std::string message;
    /* call logic part. */
    ErrorBase errorbase;
    LOGIC logic(whiteAuth);
    
    /* first auth white list. */
    bool first = logic.FirstAuth_WhiteList();

    /* not pass white list. */
    if (first == false)
    {
        header = logic.headerPart("403");
        body = errorbase.format_globalerror(header["incode"], header["description"]); 
        message = logic.bodyPart("403", header["header"], body);

    /* pass white list. */
    }else{
        logger::GetInstance().LOG("DEBUG", "InputData", _inputdata);
        logger::GetInstance().LOG("DEBUG", "UrlMethod", _urlmethod);
        /* judge user data put method. */
        int dataput = logic.dataPutJudge(_userMethod); 

        /* GET Part */
        if (dataput == 1){
            bool checkget = logic.getMethodcheck(_urlmethod, _inputlength);         
            if (checkget == true)
            {
                header = logic.headerPart("200"); 
                /* Read help from ini file. */
                INIReader reader("config.ini");
                std::string body;

                /* Read config file Failed.*/
                if (reader.ParseError() < 0)
                {
                    body = "Could not found help information.";

                /* Read config file Success.*/
                }else{
                    std::string headone = reader.Get("HELP","headone","Could not found help information.");
                    std::string headtwo = reader.Get("HELP","headtwo","");
                    std::string htmlbody = reader.Get("HELP","body","");
                    body = logic.helpbodyPart(headone, headtwo, htmlbody);
                }
                message = logic.bodyPart("200", header["header"], body);
            }else{
                header = logic.headerPart("404");
                body = errorbase.format_globalerror(header["incode"], header["description"]); 
                message = logic.bodyPart("404", header["header"], body);
            }

        /* POST Part*/
        }else if (dataput == 2){
            /* --- Part 3. analyst user input and verifty. 
                 : 400 : lack of =
                 : 401 : no auth variable
                 : 402 : auth failed.
                 : 405 : sql injection match
                 : 200 : ok. */

           BASICALG basicalgorithm;

           /* --- Part 1. check user method exit and allow 
            * on error will return 406, 407 here.
           --- */
           std::map<std::string, std::string> accessMethod = logic.getAccessMethod(_urlmethod.substr(1));
           if (accessMethod["Status"] == "true")
           {
                if (accessMethod["Method"] == "407" or \
                        accessMethod["Method"] == "410")
                {
                    /* method not found. will return 407 & 410 */
                    header = logic.headerPart(accessMethod["Method"]); 
                    body = errorbase.format_globalerror(header["incode"], header["description"]); 
                    message = logic.bodyPart(accessMethod["Method"], header["header"], body);
                }
                else
                {
                    /* --- Part 2. check user input data. ---*/
                    // a. decode base64 
                    //std::string decodedata = logic.getPostVerifty(_inputdata);
                    std::string decodedata = basicalgorithm.UrlDecode(_inputdata);
                    // b. check md5sum
                    std::map<std::string, std::string> getData = logic.getCorrectData(_urlmethod.substr(1), decodedata);
                    if (getData["Status"] == "200")
                    { 
                        /*** 
                            check data and get all logic return here. 
                        ***/
                        getData.erase("Status");
                        std::map<std::string, std::string> getdoing = logic.DoingInputVariable(accessMethod, getData);
                        header = logic.headerPart(getdoing["Info"]);
                        message = logic.bodyPart(getdoing["Info"], header["header"], getdoing["body"]);
                        /*
                        if (getdoing["Status"] != "success")
                        {
                            header = logic.headerPart(getdoing["Info"]);
                            message = logic.bodyPart(getdoing["Info"], header);
                        }else{
                            header = logic.headerPart(getdoing["Info"]);
                            message = logic.bodyPart(getdoing["Info"], header, getdoing["body"]);
                        }
                        */
                    }else{ 
                        //{"code":0,"dataObject":null,"incode":"200","strInfo":"None"}
                        header = logic.headerPart(getData["Status"]);
                        body = errorbase.format_globalerror(header["incode"], header["description"]);
                        message = logic.bodyPart(getData["Status"], header["header"], body);
                    }
                }

           /* method not allowed. will return 406. */
           }else{
               header = logic.headerPart(accessMethod["Method"]);
               body = errorbase.format_globalerror(header["incode"], header["description"]); 
               message = logic.bodyPart(accessMethod["Method"], header["header"], body);
           }
                
        }else{
            header = logic.headerPart("500");
            body = errorbase.format_globalerror(header["incode"], header["description"]); 
            message = logic.bodyPart("500", header["header"], body);
        }
    }

    logger::GetInstance().LOG("DEBUG", "ReturnMessage", message);
    return message;
}
