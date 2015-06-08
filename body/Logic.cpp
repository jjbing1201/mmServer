#include <vector>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>

#include "Logic.h"

LOGIC::LOGIC(bool Auth)
{
    whiteauth = Auth;
}

LOGIC::~LOGIC()
{
    bool whiteauth = false;
}

bool LOGIC::FirstAuth_WhiteList()
{
    return whiteauth;
}

// ------------- Protected --------------------

/*
@param : data : ex user data
@example : a=1&b=2

This method used to check ex user data
if user data has auth, this auth must correct with verifty
and will return "200", data
otherwise user data has not auth will return "401", data
*/
std::map<std::string, std::string> LOGIC::postAnalyst(const std::string & data)
{
    /* split statement. */
    unsigned int i;

    /* check verifty statement; */
    int check = 0;
    std::map<std::string, std::string> result;

    std::vector<std::string> part = split(data, "&");

    for (i=0; i<part.size(); i++)
    {
        /* get each of variable : key:value 
           if data not correct will return 400:Bad Input Data Format
        */
        std::string::size_type equals = part[i].find("=");
        if (equals != std::string::npos)
        {
            std::string key = part[i].substr(0, equals);
            std::string value = part[i].substr(equals+1);
            if (key == "auth")
            {
                check = 1;
            }else if(key == value){
                result["405"]="SQL Injection";
            }
            result[key]=value;
        }else{
            result["400"]="Bad Input Data Format."; 
            return result;
        }
    
    }

    /* check user input data. content about : auth */
    if (check == 1)
    {
        result["200"]="All right.";
    }else{
        result["401"]="No auth";
    }
    return result;
}

bool LOGIC::interface_using(std::string get_interface_name)
{
    /* Statement */
    MIWA_INTERFACE_USING interface_using;
    uint32 nowtime = nowtimestamp();
    std::string now_time = anytostr(nowtime);

    /* select interface exist. */
    std::map<std::string, std::string> interface_exist_return =
        interface_using.select_one_interface(get_interface_name);
    // <<<<<< not exist. 
    if (interface_exist_return["Status"] != "success")
    {
        std::map<std::string, std::string> insert_return = 
            interface_using.insert_INTERFACE_USING(get_interface_name, 
            now_time, "0");
        if (insert_return["Status"] == "success")
            return true;
        else
            return false;
    }
    // <<<<<< exist then update.
    else
    {
        std::map<std::string, std::string> update_return = 
            interface_using.update_one_interface(get_interface_name);
        if (update_return["Status"] == "success")
            return true;
        else
            return false;
    }

    return false;
}

// ------------- Public --------------------
/*
@param :  urlmethod
@example : /help
@param : length 
@example : 0

This method used to check user input url method correct.
if user input help method and not input any other data
will return true, otherwise, return false;
*/
bool LOGIC::getMethodcheck(const std::string & method, int length)
{
    if (method == "/help" and length == 0)
    {
        return true;
    }else{
        return false;
    }
}


/*
@param : userMethod
@example : GET, POST....
@return : int status
This method used to check user put data method
if method unknown, will return < 0
if method > 1, all right.
    return 1 : GET 
    return 2 : POST
*/
int LOGIC::dataPutJudge(const std::string & method)
{
    if (method == "GET"){
        return 1;
    }else if (method == "POST"){
        return 2;
    }else{
        return 0;
    }
}

/*
@param : urlmethod
@example :  /ZoneInfo/select

This method used to analyst post url method
will return map : map<string, string>
right return : map<tablename, operation>
error return : map<None, None>
*/
std::map<std::string, std::string> LOGIC::analystUrlMethod(std::string & urlmethod)
{
    std::map<std::string, std::string> newmap;
     
    std::string::size_type _location = urlmethod.substr(1).find("/");
    if (_location != std::string::npos)
    {
        newmap[urlmethod.substr(1).substr(0, _location)] = urlmethod.substr(1).substr(_location+1);
    }else{
        newmap["None"] = "None";
    }
    return newmap;
}

/*
@param : userinput
@example : YT0xJmI9Mg==

This method used to analyst userinput data
and get verifty by base64 again.
verifty = result[0,8]
so: user input data must connect with : verify=result
*/
std::string LOGIC::getPostVerifty(const std::string & userinput)
{
    /* self lib base64 statement. */
    BASICALG basicalgorithm;
    
    std::string baseUserinput = basicalgorithm.base64_decode(userinput);

    return baseUserinput;
}

/*
@param : data
@example : a=1&b=2
@param : verifty
@example : AAABBCCD

This method will return right data to user 
data will return like key:value  
*/
std::map<std::string, std::string> LOGIC::getCorrectData(const std::string & urlmethod, const std::string & data)
{
    /* statement return map. */
    std::map<std::string, std::string> returnmap;

    /* insize using protected method analyst data. */ 
    std::map<std::string, std::string> analystafter = postAnalyst(data);

    /* analyst data. check verifty. */
    std::map<std::string, std::string>::iterator it;
    for (it=analystafter.begin(); it!=analystafter.end(); ++it)
    {
        if ((it->first) == "400" or (it->first) == "401" or (it->first) == "405")
        {
            returnmap["Status"] = it->first;  
            return returnmap;

        /* check verifty part. */
        }else if((it->first) == "200"){

            /* ---------- inside. ------------ */
            // <<<<< For World >>>>> 
            if(urlmethod == "ServerConnect" || urlmethod == "UserLogin" || urlmethod == "UserLoginBaseData" || urlmethod == "UserVerifyCode" || urlmethod == "UserRegister" || urlmethod == "UserPrivateFillin" || urlmethod == "UserResetPass" || urlmethod == "UserMessageNotification" || urlmethod == "UserMessageList" || urlmethod == "UserDataNotification")
            {
                std::string combine =  analystafter["timestamp"]+"+"\
                                        +analystafter["data"]+"+"\
                                        +urlmethod;
                MD5 md5(combine);
                std::string md5check = md5.md5();

                if (md5check.substr(0,32) == analystafter["auth"])
                {
                    returnmap["Status"] = "200";
                }else{
                    returnmap["Status"] = "402";
                }
            }

        /* input data into map. */
        }else if ((it->first) == "auth"){
        }else{
	    if ((it->first) == "data") {
		returnmap[(it->first)] = getPostVerifty(it->second);
	    } else {
                returnmap[(it->first)] = it->second;
	    }
        }
    } 

    return returnmap;
}

/*
@param : urlmethod
@example : method1

This method used to get real access method from url method
such as : /method1 -> updateProject
and will return updateProject if right, "None" will be return 
when error occured.
*/
std::map<std::string, std::string> LOGIC::getAccessMethod(const std::string & urlmethod)
{
    uint32 i; 
    std::map<std::string, std::string> judgemethod;

    /* check user has another '/' or '/''/' */
    std::string::size_type tmp = urlmethod.find("/");
    if (tmp != std::string::npos)
    {
        /* method not allow. */
        judgemethod["Status"]="false";        
        judgemethod["Method"]="406";
    }else{
        
        /* check right method. 
           if get right method, will return method 
           or get error method, will return None. 
           but status is true.
        */
        uint32 table_size = sizeof(interfaceName)/sizeof(_interHandler);
        for(i=0; i<table_size; i++)
        {
            if (urlmethod == interfaceName[i].name && \
                             interfaceName[i].status == 1)
            {
                judgemethod["Status"]="true";
                judgemethod["Method"]=urlmethod;
                judgemethod["Package"]=interfaceName[i].package;
                break;
            }
            else if (urlmethod == interfaceName[i].name && \
                                  interfaceName[i].status == 0)
            {
                judgemethod["Status"]="true";
                judgemethod["Method"]="410";
                judgemethod["Package"]="-1";
                break;
            }
            else
            {
                judgemethod["Status"]="true";
                judgemethod["Method"]="407";
                judgemethod["Package"]="-1";
            }
        }
    }

    return judgemethod;
}

/* 
@param : method
@example : updateProject
@param : data
@example : map object

This method used to test input is correct.
and will return test result to user.

*/
std::map<std::string, std::string> LOGIC::DoingInputVariable(std::map<std::string, std::string> getAccessReturn, std::map<std::string, std::string> data)
{
    /* statement return. */
    std::map<std::string, std::string> result;

    /* Global Interface using Record. */
    //interface_using(getAccessReturn["Method"]);
     
    /* ---------- 
        inside. 
    ------------ */
    if (getAccessReturn["Package"] == "1")
    {
        using namespace N_WORLD;
        WORLD_MAIN worldmain;
        try
        {
            result = worldmain.into_process(getAccessReturn, data);
            return result;
        }
        catch(...)
        {
            goto error_return;
        }
    }

error_return:
    result["Status"] = "failed";
    result["Info"] = "500";
    result["body"] = "Internal Server Error from Method";
    return result;

    return result;
}

/*
@param : status 
@param example : "200", "404"....
@return : string buf

This method used to combine return buf 1-3 line 
and variable only accept and check for:
    200 -> ok 
    403 -> white list forbidden
    404 -> not found method
    500 -> right message, error when doing. 
*/
std::map<std::string, std::string> LOGIC::headerPart(std::string status)
{
    std::map<std::string, std::string> result;

    std::string statusExplain;
    if (status == "200")
    {
        statusExplain = HTTP_RESPONSE_OK;
    }
    else if (status == "400")
    {
        statusExplain = HTTP_RESPONSE_BAD_REQUEST;
    }
    else if (status == "401")
    {
        statusExplain = HTTP_RESPONSE_NO_AUTH;
    }
    else if (status == "402")
    {
        statusExplain = HTTP_RESPONSE_AUTH_FAILED;
    }
    else if (status == "403")
    {
        statusExplain = HTTP_RESPONSE_FORBIDDEN;
    }
    else if (status == "404")
    {
        statusExplain = HTTP_RESPONSE_NOTFOUND;
    }
    else if (status == "405")
    {
        statusExplain = HTTP_RESPONSE_SQL_INJECTION;
    }
    else if (status == "406")
    {
        statusExplain = HTTP_RESPONSE_METHOD_NOT_ALLOW;
    }
    else if (status == "407")
    {
        statusExplain = HTTP_RESPONSE_METHOD_NOT_FOUND;
    }
    else if (status == "408")
    {
        statusExplain = HTTP_RESPONSE_OP_FAILED;
    }
    else if (status == "409")
    {
        statusExplain = HTTP_RESPONSE_CMD_FAILED;
    }
    else if (status == "410")
    {
        statusExplain = HTTP_RESPONSE_METHOD_CANCELD;
    }
    else if (status == "500")
    {
        statusExplain = HTTP_RESPONSE_FATAL;
    }
    else
    {
        statusExplain = HTTP_RESPONSE_UNKNOWN;
    }
    
    
    /* part of header : 1-3 line. */
    std::string header;
    /* first line. */
    header += "HTTP/1.1 "+status+" "+statusExplain+"\r\n";
    /* second line. */
    header += "Server: mmServer/v1.0.3_101\r\n";
    /* third line. */
    header += "Content-Type: text/html\r\n";
    /* fourth line. */ 
    header += "Access-Control-Allow-Origin: *\r\n";
    /* fifth line. */
    header += "Access-Control-Allow-Headers: X-Requested-With\r\n";
        
    
    result["incode"] = status;
    result["header"] = header;
    result["description"] = statusExplain;

    return result;
}

std::string LOGIC::bodyPart(std::string status, std::string & header)
{
    if (status == "400"){
        /* forth line. */
        header += "Content-Length: 14\r\n";
        /* fifth line. */ 
        header += "\r\n";
        /* Sixth line. */ 
        header += "Bad Request.\r\n";
    }else if (status == "401"){ 
        /* forth line. */
        header += "Content-Length: 19\r\n";
        /* fifth line. */ 
        header += "\r\n";
        /* Sixth line. */ 
        header += "No Auth Variable.\r\n";
    }else if (status == "402"){ 
        /* forth line. */
        header += "Content-Length: 14\r\n";
        /* fifth line. */ 
        header += "\r\n";
        /* Sixth line. */ 
        header += "Auth Failed.\r\n";
    }else if (status == "403"){
        /* forth line. */
        header += "Content-Length: 16\r\n";
        /* fifth line. */
        header += "\r\n";
        /* Sixth line. */
        header += "403 Forbidden.\r\n";
    }else if(status == "404"){
        /* forth line. */
        header += "Content-Length: 15\r\n";
        /* fifth line. */
        header += "\r\n";
        /* Sixth line. */
        header += "404 NotFound.\r\n";
    }else if(status == "405"){ 
        /* forth line. */
        header += "Content-Length: 31\r\n";
        /* fifth line. */ 
        header += "\r\n"; 
        /* Sixth line. */ 
        header += "SQL Injection Variable Match.\r\n"; 
    }else if(status == "406"){
        /* forth line. */
        header += "Content-Length: 21\r\n";
        /* fifth line. */
        header += "\r\n";
        /* Sixth line. */
        header += "Method Not Allowed.\r\n";
    }else if(status == "407"){
        /* forth line. */
        header += "Content-Length: 19\r\n";
        /* fifth line. */
        header += "\r\n";
        /* Sixth line. */
        header += "Method Not Found.\r\n";
    }else if(status == "408"){
        /* forth line. */
        header += "Content-Length: 19\r\n";
        /* fifth line. */
        header += "\r\n";
        /* Sixth line. */
        header += "Operation Failed.\r\n";
    }else if(status == "409"){
        /* forth line. */
        header += "Content-Length: 19\r\n";
        /* fifth line. */
        header += "\r\n";
        /* Sixth line. */
        header += "CMD Check Failed.\r\n";
    }else if(status == "410"){
        /* forth line. */
        header += "Content-Length: 30\r\n";
        /* fifth line. */
        header += "\r\n";
        /* Sixth line. */
        header += "Interface has been canceled.\r\n";
    }else if(status == "500"){
        /* forth line. */ 
        header += "Content-Length: 28\r\n";
        /* fifth line. */
        header += "\r\n"; 
        /* Sixth line. */ 
        header += "500 Internal Server Error.\r\n";   
    }

    return header;
}

/*
@param : status : user update status
@example : 200
@param : header : first three line.
@param : body : user pass data and will count length and add to message

This method is Reconstruction about message.
user will input another data what they want to add into message.
 
*/
std::string LOGIC::bodyPart(std::string status, std::string & header, std::string & body)
{

    //if (status == "200")
    //{
        /* forth line. */
    std::stringstream mid;
    std::string bodylengthstr;
    mid << body.size();
    mid >> bodylengthstr;
 
    header += "Content-Length: "+bodylengthstr+"\r\n";

    /* fifth line. */
    header += "\r\n";     

    /* Sixth line. */
    header += body + "\r\n";
    //}

    return header;
}

/*
@param : headOne : html <h1> Content <h1/>
@param : headTwo : html <h2> Content <h2/>
@param : body : html <p> Content <p/>

This method used to combine help body and return
user will input nothing but get from config file section [HELP] part
*/
std::string LOGIC::helpbodyPart(const std::string & headOne, const std::string & headTwo, const std::string & body)
{
    /* statement part variable. */
    std::string result;

    result += "<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\"><title></title><style>*{ margin: 0;}body { background-color: #c6e0e1;}h1{ margin-bottom: 20px;padding-left: 10px; font-size:50px; line-height: 60px; border-bottom: 1px solid #ccc; border-left: 10px solid #690; }h2{ margin: 0 0 20px 10px;padding-left: 10px; font-size: 30px; line-height: 40px; border-bottom: 1px solid #CCC; }p{ margin: 0 0 0 10px;padding-left: 10px;}</style></head>";
    result += "<body><h1>"+headOne+"</h1>";
    result += "<h2>"+headTwo+"</h2>";
    result += "<p>"+body+"</p></body></html>\r\n";
    return result;
}
