#include "Graph.h"

	/*Scene_graph::Scene_graph(string root){
		this->root_id = root;
	}

	void Scene_graph::process_object(string id){
		Node *n = graph[id];
		glMultMatrixf(&(n->transforms[0]));
		n->draw();
		glPushMatrix();
		for(vector<string>::iterator it = n->children.begin();it!=n->children.end();it++){
			process_object(*it);
		}
		glPopMatrix();
	}*/

    Graph::Graph(string rootid)
    {
        this->rootid = rootid;
    }
    
    Graph::~Graph()
    {
        
    }

void Graph::setRootId(string rootid)
    {
        this->rootid = rootid;
    }

string Graph::getRootId()
    {
        return this->rootid;
    }

    void Graph::addNode(Node* newNode)
    {
        //nodesMap
    }