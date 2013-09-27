#ifndef _GRAPH_H
#define _GRAPH_H

#include "Node.h"
#include <map>
#include <vector>
#include <string>

namespace scene{

	using namespace std;

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
        string rootid = "0";
        map<string, Node*> nodesMap; // the graph is a set of nodes stored in a <map>
    
    public:
        Graph(string rootid);
        ~Graph();
        void addNode(Node*);
};


} //scene

#endif