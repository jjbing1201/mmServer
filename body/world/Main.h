#ifndef _WORLD_MAIN_
#define _WORLD_MAIN_

#include "world_include.h"

#include "Check.h"
#include "Format.h"
#include "Operation.h"
#include "Serverreturn.h"

namespace N_WORLD
{
    class WORLD_MAIN : public METHOD
    {
    protected:
        /*
         *  brief   : change status of this world using. 
         *            bool -> check
         *            bool -> operation
         *            bool -> serverreturn
         *            bool -> format
        */
        void change_process(bool, bool, bool, bool);
    
    public:
        WORLD_MAIN(bool check=true, bool operation=true, \
                     bool serverreturn=true, bool format=true) : \
                     METHOD(check, operation, serverreturn, format) {}
    
        virtual ~WORLD_MAIN() {}
    
        std::map<std::string, std::string> into_process(\
                        std::map<std::string, std::string>, \
                        std::map<std::string, std::string>);
    
    };
};
#endif /* _WORLD_MAIN_ */

