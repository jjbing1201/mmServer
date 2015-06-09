#include "AlgorithmHash.h"
#include "../shared/util.h"

BaseDataCycle::BaseDataCycle() 
{
    conhash = conhash_init(NULL);
    setAllNode();
}

BaseDataCycle::~BaseDataCycle()
{
    conhash_fini(conhash);
}

void BaseDataCycle::setAllNode()
{
    int i;
    if (conhash) {
        for (i=0; i<256; i++) {
	     std::string nodeName = anytostr(i);
	     conhash_set_node(&global_nodes[i], nodeName.c_str(), 50);
	     conhash_add_node(conhash, &global_nodes[i]);
        }
    } 
    return;
}

std::map<std::string, std::string> BaseDataCycle::nodeGet(std::string data)
{
    std::map<std::string, std::string> result;

    node = conhash_lookup(conhash, data.c_str());
    if (node) {
	result["nodeId"] = node->iden;
        result["giveString"] = data;
    } else {
	result["nodeId"] = "0";
        result["giveString"] = data;
    }

    return result;
}
