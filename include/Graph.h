#ifndef _GRAPH_H
#define _GRAPH_H

#include "Node.h"
#include <map>
#include <vector>
#include <string>

namespace scene{

	using namespace std;

	class Scene_graph{
	public:
		Scene_graph(string root);
		~Scene_graph();
		void process_object(string id);
	private:
		string root_id;
		map<string,Node*> graph;

	};
} //scene





#endif