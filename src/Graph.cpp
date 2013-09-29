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

void Graph::setNodes(map<string, Node*> nodesMap)
{
    this->nodesMap = nodesMap;
}

void Graph::addNode(Node* newNode)
{
    nodesMap[newNode->getId()] = newNode; // add node to the graph
}

Node* Graph::getNodeById(string id)
{
    Node* nodeFound = new Node();
    map<string, Node*>::const_iterator pos = nodesMap.find(id);
    
    if (pos == nodesMap.end()) {
        // node not found
        cout << "Node with the id '" << id << "' not found" << endl;
        
    } else {
        // node found
        nodeFound = pos->second; // the node with the wanted id
    }
    
    return nodeFound;
    
}

string Graph::getRootId()
{
    return this->rootid;
}

map<string, Node*> Graph::getNodes()
{
    return this->nodesMap;
}