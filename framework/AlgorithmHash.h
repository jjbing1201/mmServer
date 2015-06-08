#ifndef _ALGORITHM_CONHASH_HEADER_
#define _ALGORITHM_CONHASH_HEADER_

#include <iostream>
#include <map>
#include "SingleTon.h"
#include "header/conhash.h"

class BaseDataCycle
{
private:
    int i;
    const struct node_s *node;
    char str[128];
    long hashes[512];
	struct node_s global_nodes[256];
    struct conhash_s *conhash;
   
    void setAllNode();

public:
    BaseDataCycle();
    virtual ~BaseDataCycle();

    std::map<std::string, std::string> nodeGet(std::string data);
};

#endif /* _ALGORITHM_CONHASH_HEADER_ */

typedef SINGLETON<BaseDataCycle> bdhash;
