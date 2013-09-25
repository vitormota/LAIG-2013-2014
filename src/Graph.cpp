#include "Graph.h"

namespace scene{

	Scene_graph::Scene_graph(string root){
		this->root_id = root;
	}

	void Scene_graph::process_object(string id){
		Node *n = graph[id];
		glMultMatrixf(&(n->trasnforms[0]));
		n->draw();
		glPushMatrix();
		for(vector<string>::iterator it = n->children.begin();it!=n->children.end();it++){
			process_object(*it);
		}
		glPopMatrix();
	}


}//scene