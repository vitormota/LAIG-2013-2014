#include "Graph.h"

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
    this->nodesMap = map<string,Node*>();
    this->nodesMap.insert(nodesMap.begin(),nodesMap.end());
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
        // the node with the wanted id
        nodeFound = nodesMap[id];
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