#ifndef _INTERFACE_MASTER_
#define _INTERFACE_MASTER_

#define HTTP_RESPONSE_OK                "OK"
#define HTTP_RESPONSE_UNKNOWN           "Unknown"
#define HTTP_RESPONSE_BAD_REQUEST       "Bad Request"
#define HTTP_RESPONSE_NO_AUTH           "No Auth"
#define HTTP_RESPONSE_AUTH_FAILED       "Auth Failed"
#define HTTP_RESPONSE_FORBIDDEN         "Forbidden"
#define HTTP_RESPONSE_NOTFOUND          "Not Found"
#define HTTP_RESPONSE_SQL_INJECTION     "SQL Injection Var"
#define HTTP_RESPONSE_METHOD_NOT_ALLOW  "Method Not Allowed"
#define HTTP_RESPONSE_METHOD_NOT_FOUND  "Method Not Found"
#define HTTP_RESPONSE_OP_FAILED         "Operation Failed"
#define HTTP_RESPONSE_CMD_FAILED        "CMD Check Failed."
#define HTTP_RESPONSE_METHOD_CANCELD    "Interface has been canceled."
#define HTTP_RESPONSE_FATAL             "Internal Server Error"

typedef struct intefaceHandler
{
    char name[32];
    uint32 status;      // interface could be used or not
                        // 0 or cancel, 1 for support
    char package[2];    // dpart each of data.
    char version[13];
} _interHandler;

const _interHandler interfaceName[] =
{
    /* <<<<<<< Part 1. World For App >>>>>>>>>>>>>>> */
    {"ServerConnect", 1, "1", "1.0.3_0607"},
    {"UserLogin", 1, "1", "1.0.3_0607"},
    {"UserLoginBaseData", 1, "1", "1.0.3_0607"},
    {"UserVerifyCode", 1, "1", "1.0.3_0607"},
    {"UserRegister", 1, "1", "1.0.3_0607"},
    {"UserPrivateFillin", 1, "1", "1.0.3_0608"},
    {"UserResetPass", 1, "1", "1.0.3_0608"},
    {"UserMessageNotification", 1, "1", "1.0.3_0608"},
    {"UserMessageList", 1, "1", "1.0.3_0608"},
    {"UserDataNotification", 1, "1", "1.0.3_0608"},
    {"UserHelpList", 1, "1", "1.0.3_0608"},
    {"UserMessageEachCheck", 1, "1", "1.0.3_0609"},
    {"UserCheckVerifyCode", 1, "1", "1.0.3_0613"}
};

#endif /* _INTERFACE_MASTER_ */
