#ifndef _GRAPH_H
#define _GRAPH_H

#include "Node.h"
#include <map>
#include <string>
#include <iostream>

using std::string;
using std::map;
using std::cout;
using std::endl;

class Graph
{
    private:
        string rootid;
        map<string, Node*> nodesMap; // the graph is a set of nodes stored in a <map>
    
    
    public:
        Graph(string rootid);
        ~Graph();
        void setRootId(string rootid);
        void addNode(Node*);
        void setNodes(map<string, Node*> nodesMap);
        string getRootId();
        Node* getNodeById(string id);
        map<string, Node*> getNodes();
    
};

#endif