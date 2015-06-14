#include "Main.h"

using namespace N_WORLD;

void WORLD_MAIN::change_process(bool check, bool operation, \
                                        bool serverreturn, bool format)
{
    change_has_check(check);
    change_has_operation(operation);
    change_has_serverreturn(serverreturn);
    change_has_format(format);
    return;
}

std::map<std::string, std::string> WORLD_MAIN::into_process(\
                        std::map<std::string, std::string> method, \
                        std::map<std::string, std::string> data)
{
    /* Statement about return => result. */
    std::map<std::string, std::string> result;
    std::map<std::string, std::string> last_step;

    /* Step 1. throught method to ensure status about each process. */
    if (method["Method"] == "ServerConnect" ||
	method["Method"] == "UserMessageNotification" ||
	method["Method"] == "UserMessageList" ||
	method["Method"] == "UserHelpList" ||
	method["Method"] == "UserCheckVerifyCode" ||
	method["Method"] == "UserLoginBaseData")
        change_process(true, false, true, true);

    else if (method["Method"] == "UserLogin" || 
	     method["Method"] == "UserVerifyCode" || 
	     method["Method"] == "UserRegister" ||
	     method["Method"] == "UserResetPass" ||
	     method["Method"] == "UserPrivateFillin" ||
	     method["Method"] == "UserMessageEachCheck" ||
	     method["Method"] == "UserDataNotification")
	change_process(true, true, false, true);

    /* Step 2. into process step one by one. */

    // 2.1 check part.
    WORLDCHECK worldcheck;
    WORLDOPERATION worldoperation;    
    WORLDRETURN worldreturn;
    WORLDFORMAT worldformat;

    if ( (get_has_check()) == true )
    {
        last_step = worldcheck.check_inter(method["Method"], data);
        if (data["Status"] == "false")
            goto process_step_error;
    }

    // 2.2 operation part.
    if ( (get_has_operation()) == true )
    {
        last_step = worldoperation.operation_inherit(method["Method"], last_step);
        if (last_step["Status"] == "false")
            goto process_step_error;
    }

    // 2.3 serverreturn part.
    if ( (get_has_serverreturn()) == true )
    {
        last_step = worldreturn.serverreturn_inherit(method["Method"], last_step);
        if (last_step["Status"] == "false")
            goto process_step_error;
    }

    // 2.4 format part.
    if ( (get_has_format()) == true )
    {
        if (last_step["Status"] == "false")
            result = worldformat.format_inter(method["Method"], last_step);
        else
            result = worldformat.format_inter_inherit(method["Method"], last_step);
        return result; 
    }

process_step_error:
    result["Status"] = "false";
    result["Info"] = "408";
    result["body"] = "{\"code\":1, \"incode\":408, \"strInfo\":\"None\",\"dataObject\":\"None\"}\r\n";     
    return result;

    return result;
}
