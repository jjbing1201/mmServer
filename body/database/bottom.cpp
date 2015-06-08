#include "bottom.h"

DAL_Bottom::DAL_Bottom()
{

}

DAL_Bottom::~DAL_Bottom()
{

}

std::string DAL_Bottom::stringtoint(std::string resstring)
{
    /* return result. */
    std::string result;

    unsigned int count = 0; 
    unsigned int i; 
    /* Throught ASCII judge is Number. */
    for(i=0;i<resstring.size(); i++)
    { 
        if (int(resstring[i]) > 47 && int(resstring[i]) < 58)
        { 
            count += 1; 
        } 
    } 
                                                             
    if (count == resstring.size())
    { 
        result=resstring;
    }else{
        result="\""+resstring+"\"";
    }

    return result;
}

/*** ---- protected ---- ***/
std::string DAL_Bottom::updateop(std::map<std::string, std::string> upvar)
{
    /* 1. statement a normal var. */
    std::string var;

    std::map<std::string, std::string>::iterator it;
    for (it=upvar.begin(); it!=upvar.end(); it++)
    {
        std::string value = stringtoint(it->second);
        var += " , "+it->first+"="+value;
    }
    var = var.substr(2);

    return var;
}

std::string DAL_Bottom::unionop(const std::string & op, std::map<std::string, std::string> opvar)
{
    /* 1. statement a normal var. */
    std::string var;

    /* 2.1 and part */
    if (op == "_and")
    {
        std::map<std::string, std::string>::iterator it;
        for (it=opvar.begin(); it!=opvar.end(); it++)
        {
            std::string value = stringtoint(it->second);
            var += " and "+it->first+"="+value;
        }
        var = var.substr(4);
    }
    /* 2.2 or part */
    else if(op == "_or"){
        std::map<std::string, std::string>::iterator it;
        for (it=opvar.begin(); it!=opvar.end(); it++)
        { 
           std::string value = stringtoint(it->second);
           var += " or "+it->first+"="+value;
        }
        var = var.substr(3);
    }
    else if(opvar.size() == 1 and op == "None"){
        std::map<std::string, std::string>::iterator it;
        for (it=opvar.begin(); it!=opvar.end(); it++)
        { 
           std::string value = stringtoint(it->second);
           var = it->first+"="+value;
        }
    }
    else if(opvar.size() == 1 and op == "_not"){
        std::map<std::string, std::string>::iterator it;
        for (it=opvar.begin(); it!=opvar.end(); it++)
        {
           std::string value = stringtoint(it->second);
           var = it->first+"!="+value;
        } 
    }
    else if(opvar.size() == 1 and op == "_like"){
        std::map<std::string, std::string>::iterator it;
        for (it=opvar.begin(); it!=opvar.end(); it++)
        {
           std::string value = stringtoint(it->second);
           var = it->first+" like \"\%"+it->second+"\%\"";
        }
    }
    /* 2.3 > part. */ 
    else if(op == "_lt"){
        std::map<std::string, std::string>::iterator it;
        for (it=opvar.begin(); it!=opvar.end(); it++)
        {
           std::string value = stringtoint(it->second);
           var += "  "+it->first+">"+value;
        }
        var = var.substr(1);
    }
    /* 2.4 < part. */
    else if(op == "_st"){
        std::map<std::string, std::string>::iterator it;
        for (it=opvar.begin(); it!=opvar.end(); it++)
        {
           std::string value = stringtoint(it->second);
           var += "  "+it->first+"<"+value;
        } 
        var = var.substr(1);
    } 
    else{
        var = "None";
    }
    
    return var;
}

std::string DAL_Bottom::appendop(const std::string &op, std::map<std::string, std::string> opvar)
{
    /* 1. statement like return. */
    std::string likere;

    if (op == "_like" && opvar.size() == 1)
    {
        std::map<std::string, std::string>::iterator it;
        for (it=opvar.begin(); it!=opvar.end(); it++)
        {
            std::string value = stringtoint(it->second);
            likere += it->first+" like "+"\'\%"+value+"\%\'"; 
        }
    }else{
        likere = "None";
    }

    return likere;
}

std::string DAL_Bottom::appendop(const std::string &op, const std::string &columname, const std::string &sequeue)
{
    /* 1. statement about return. */
    std::string orderre;

    if (op == "_order")
    {
        if (sequeue == "_desc")
        {
            orderre += " ORDER BY "+columname+" DESC";
        }
        else if (sequeue == "_asc")
        {
            orderre += " ORDER BY "+columname+" ASC";
        }
        else if (sequeue == "_desc 1")
        {
            orderre += " ORDER BY "+columname+" DESC limit 1";
        }
        else if (sequeue == "_desc 10")
        {
            orderre += " ORDER BY "+columname+" DESC limit 10";
        }
        else if (sequeue == "limit 10")
        {
            orderre += " limit 10";
        }
    }else{
        orderre = "None";
    }
    
    return orderre;
}

std::string DAL_Bottom::formatop(const std::string &op, std::map<std::string, std::string> opvar)
{
    /* 1. statement a normal var. */
    std::string var;

    if (op == "_lt")
    {
        std::map<std::string, std::string>::iterator it;
        for (it=opvar.begin(); it!=opvar.end(); it++)
        {
           std::string value = stringtoint(it->second);
           var += "  "+it->first+">"+value;
        }
        var = var.substr(1);
    }
    /* 2.4 < part. */
    else if(op == "_st")
    {
        std::map<std::string, std::string>::iterator it;
        for (it=opvar.begin(); it!=opvar.end(); it++)
        {
           std::string value = stringtoint(it->second);
           var += "  "+it->first+"<"+value;
        }
        var = var.substr(1);
    }
    else if(op == "_stq")
    {
        std::map<std::string, std::string>::iterator it;
        for (it=opvar.begin(); it!=opvar.end(); it++)
        {
           std::string value = stringtoint(it->second);
           var += "  "+it->first+"<="+value;
        }
        var = var.substr(1);
    }
    else
    {
        var = "None";
    }

    return var;
}

/*** ---- public ---***/
std::map<int, std::string> DAL_Bottom::insert_Bottom(const std::string & tablename, int count, std::vector<std::string> variables)
{
    std::map<int, std::string> cmd;
    /* 1. check vector count correct. */
    if (variables.size() != count)
    {
        cmd[0]="false";
    }

    /* 2. analyst vector variables. */
    std::string tmpgetcmd;
    for (std::vector<std::string>::iterator it = variables.begin(); it != variables.end(); it++)
    {
        /* 2.1 judge variable is number. */
        std::string tmp = stringtoint(*it);
        tmpgetcmd += ", "+tmp;
    } 

    /* 3. combine cmd. */
    cmd[1] = "INSERT INTO "+tablename+" VALUES("+tmpgetcmd.substr(2)+");";

    return cmd;
}

std::map<int, std::string> DAL_Bottom::update_all_Bottom(const std::string & tablename, const std::string & columname, const std::string & variable)
{
    std::map<int, std::string> cmd;

    try
    {
        /* 1. check variables. */
        std::string tmp = stringtoint(variable);
    
        /* 2. combine cmd */
        //  update SubDomainList set DomainID=9 where SubDomainID=101
        cmd[1] = "UPDATE "+tablename+" SET "+columname+"="+tmp+";";
    }catch(...){
        cmd[0] = "DAL Bottom update_all_Bottom Error.";
    }

    return cmd;
}

std::map<int, std::string> DAL_Bottom::update_direct_Bottom(const std::string &tablename, std::map<std::string, std::string> upvar, \
                                                    const std::string &op, std::map<std::string, std::string> opvar)
{
    /* statement about return cmd. */
    std::map<int, std::string> cmd;

    try
    {
        /* 1. cmd -> body */
        std::string updatecombine = updateop(upvar);
        cmd[1] += "UPDATE "+tablename+" SET"+updatecombine;
    
        /* 2. cmd -> where. */
        std::string unionre = unionop(op, opvar);
        if (unionre != "None")
        {
            cmd[1] += " where "+unionre+";";
        }else{
            cmd[0] = "DAL Bottom update_direct_Bottom Var Operation input Error.";
        }

    }catch(...){
        cmd[0] = "DAL Bottom update_direct_Bottom Error.";
    }

    return cmd;
}

std::map<int, std::string> DAL_Bottom::update_direct_Bottom_compare(
                            const std::string &tablename, \
                            std::map<std::string, std::string> upvar, \
                            const std::string &op, \
                            std::map<std::string, std::string> opvar, \
                            const std::string & otherop, \
                            std::map<std::string, std::string> other_opvar)
{
    /* statement about return cmd. */
    std::map<int, std::string> cmd;

    try
    {
        /* 1. cmd -> body */
        std::string updatecombine = updateop(upvar);
        cmd[1] += "UPDATE "+tablename+" SET"+updatecombine;

        /* 2. cmd -> where. */
        std::string unionre = unionop(op, opvar);
        if (unionre != "None")
        {
            cmd[1] += " where "+unionre;
        }else{
            cmd[0] = "DAL Bottom update_direct_Bottom Var Operation input Error.";
        }

        /* 3. cmd -> format other of where */
        std::string formatre = formatop(otherop, other_opvar);
        if (formatre != "None")
        {
            cmd[1] += " and "+formatre+";";
        }
        else
        {
            cmd[1] += ";";
        }

    }catch(...){
        cmd[0] = "DAL Bottom update_direct_Bottom Error.";
    }

    return cmd;
}

std::map<int, std::string> DAL_Bottom::delete_all_Bottom(const std::string & tablename)
{
    /* statement about return cmd. */
    std::map<int, std::string> cmd;

    try
    {
        cmd[1] += "DELETE FROM "+tablename+";";
    }catch(...){
        cmd[0] = "DAL Bottom delete_all_Bottom error.";
    }

    return cmd;
}

std::map<int, std::string> DAL_Bottom::delete_direct_Bottom(const std::string & tablename, \
                                                    const std::string & op, std::map<std::string, std::string> opvar)
{
    /* statement about return cmd. */
    std::map<int, std::string> cmd;

    try
    {
        /* 1. cmd -> body */
        cmd[1] += "DELETE FROM "+tablename;

        /* 2. cmd -> where. */
        std::string unionre = unionop(op, opvar);
        if (unionre != "None")
        {
            cmd[1] += " where "+unionre+";";
        }else{
            cmd[0] = "DAL Bottom delete_single_Bottom Var Operation input Error.";
        }
    }catch(...){
        cmd[0] = "DAL Bottom delete_single_Bottom error.";
    } 
    
    return cmd;
}

std::map<int, std::string> DAL_Bottom::select_all_Bottom(const std::string & tablename)
{
    /* statement about return string. */
    std::map<int, std::string> cmd;

    try
    {
        /* 1. cmd -> get body. */
        cmd[1] += "SELECT * FROM "+tablename+";";
    }catch(...){
        cmd[0] = "DAL Bottom select_all_Bottom Error.";
    }
    
    return cmd;
}

std::map<int, std::string> DAL_Bottom::select_direct_Bottom(const std::string & tablename, \
                                                     const std::string & op, std::map<std::string, std::string> opvar)
{
    /* statement about return cmd. */ 
    std::map<int, std::string> cmd; 

    try
    {
        /* 1. cmd -> body */
        cmd[1] += "SELECT * FROM "+tablename;

        /* 2. cmd -> where. */
        std::string unionre = unionop(op, opvar);
        if (unionre != "None")
        {
            cmd[1] += " where "+unionre+";";
        }else{
            cmd[0] = "DAL Bottom select_direct_Bottom Var Operation input Error."; 
        }
    }catch(...){
        cmd[0] = "DAL Bottom select_direct_Bottom error.";
    }
    
    return cmd;
}

std::map<int, std::string> DAL_Bottom::select_direct_Bottom_bycount(\
                        const std::string &tablename, \
                        const std::string & op, \
                        std::map<std::string, std::string> opvar)
{
    /* statement about return cmd. */
    std::map<int, std::string> cmd;

    try
    {
        /* 1. cmd -> body */
        cmd[1] += "SELECT count(*) FROM "+tablename;

        /* 2. cmd -> where. */
        std::string unionre = unionop(op, opvar);
        if (unionre != "None")
        {
            cmd[1] += " where "+unionre+";";
        }else{
            cmd[0] = "DAL Bottom select_direct_Bottom Var Operation input Error";
        }
    }catch(...){
        cmd[0] = "DAL Bottom select_direct_Bottom error.";
    }

    return cmd;
}


std::map<int, std::string> DAL_Bottom::select_direct_Bottom_asc(const std::string & tablename, \
                             const std::string & op, std::map<std::string, std::string> opvar, \
                             std::string column)
{           
    /* statement about return cmd. */
    std::map<int, std::string> cmd;
        
    try
    {
        /* 1. cmd -> body */
        cmd[1] += "SELECT * FROM "+tablename;

        /* 2. cmd -> where. */
        std::string unionre = unionop(op, opvar);
        if (unionre != "None")
        {
            cmd[1] += " where "+unionre+" order by cast("+column+" as unsigned) asc;";
        }else{              
            cmd[0] = "DAL Bottom select_direct_Bottom Var Operation input Error.";
        }
    }catch(...){
        cmd[0] = "DAL Bottom select_direct_Bottom error.";
    }
    
    return cmd;
}       

std::map<int, std::string> DAL_Bottom::select_direct_Bottom(const std::string & tablename, \
                                                     const std::string & op, std::map<std::string, std::string> opvar, \
                                                     const std::string & otherop, std::map<std::string, std::string> other_opvar)
{
    /* statement about return cmd. */
    std::map<int, std::string> cmd;

    try
    {
        /* 1. cmd -> body */
        cmd[1] += "SELECT * FROM "+tablename;

        /* 2. cmd -> where. */
        std::string unionre = unionop(op, opvar);
        if (unionre != "None")
        {
            cmd[1] += " where "+unionre;
        }else{
            cmd[0] = "DAL Bottom select_direct_Bottom Var Operation input Error.";
        }

        /* 3. cmd -> format other of where */
        std::string formatre = formatop(otherop, other_opvar);
        if (formatre != "None")
        {
            cmd[1] += " and "+formatre+";";
        }
        else
        {
            cmd[1] += ";";
        }
    }catch(...){
        cmd[0] = "DAL Bottom select_direct_Bottom error.";
    }

    return cmd;
}

std::map<int, std::string> DAL_Bottom::select_direct_Bottom_order(
                            const std::string & tablename, \
                            const std::string & op, \
                            std::map<std::string, std::string> opvar, \
                            const std::string & otherop, \
                            std::string other_opvar,\
                            const std::string & scqueueop)
{
    /* statement about return cmd. */
    std::map<int, std::string> cmd;

    try
    {
        /* 1. cmd -> body */
        cmd[1] += "SELECT * FROM "+tablename;

        /* 2. cmd -> where. */
        std::string unionre = unionop(op, opvar);
        if (unionre != "None")
        {
            cmd[1] += " where "+unionre;
        }else{
            cmd[0] = "DAL Bottom select_direct_Bottom Var Operation input Error.";
        }

        /* 3. cmd -> format other of where */
        std::string formatre = appendop(otherop, other_opvar, scqueueop);
        if (formatre != "None")
        {
            cmd[1] += " "+formatre+";";
        }
        else
        {
            cmd[1] += ";";
        }
    }catch(...){
        cmd[0] = "DAL Bottom select_direct_Bottom error.";
    }

    return cmd;
}

std::map<int, std::string> DAL_Bottom::select_direct_Bottom_com_order(
                                const std::string & tablename, \
                                const std::string & op, \
                                std::map<std::string, std::string> opvar, \
                                const std::string & otherop, \
                                std::map<std::string, std::string> other_opvar, \
                                const std::string & orderop, \
                                std::string order_opvar,\
                                const std::string & scqueueop)
{
    /* statement about return cmd. */
    std::map<int, std::string> cmd;

    try
    {
        /* 1. cmd -> body */
        cmd[1] += "SELECT * FROM "+tablename;

        /* 2. cmd -> where. */
        std::string unionre = unionop(op, opvar);
        if (unionre != "None")
        {
            cmd[1] += " where "+unionre;
        }else{
            cmd[0] = "DAL Bottom select_direct_Bottom Var Operation input Error.";
        }

        /* 3. cmd -> format other of where */
        std::string formatre = formatop(otherop, other_opvar);
        if (formatre != "None")
        {
            cmd[1] += " and "+formatre;
        }
        else
        {
            cmd[1] += ";";
        }

        /* 3. cmd -> format other of where */
        std::string formatres = appendop(orderop, order_opvar, scqueueop);
        if (formatre != "None")
        {
            cmd[1] += " "+formatres+";";
        }
        else
        {
            cmd[1] += ";";
        }
    }catch(...){
        cmd[0] = "DAL Bottom select_direct_Bottom error.";
    }

    return cmd;
}

