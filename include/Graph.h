#ifndef _GRAPH_H
#define _GRAPH_H

#include "Node.h"
#include <map>
#include <vector>
#include <string>

using std::string;
using std::vector;
using std::map;

	/*class Scene_graph{
	public:
		Scene_graph(string root);
		~Scene_graph();
		void process_object(string id);
	private:
		string root_id;
		map<string,Node*> graph;

	};*/

class Graph
{
    private:
        string rootid;
        map<string, Node*> nodesMap; // the graph is a set of nodes stored in a <map>
    
    public:
        Graph(string rootid);
        ~Graph();
        void setRootId(string rootid);
        string getRootId();
        void addNode(Node*);
};



#endif