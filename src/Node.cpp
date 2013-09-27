#include "Node.h"

namespace scene{


	/// <summary>
	/// Initializes a new instance of the <see cref="Node"/> class.
	/// Only copies node name
	/// </summary>
	/// <param name="n">The n.</param>
	/*Node::Node(const Node id){
		this->name=n.name;
		//////
	}*/

    Node::Node(string id)
    {
        this->id = id;
    }
    
    Node::~Node()
    {
        
    }
    
    /*Node::~Node(){
		//delete[] trasnforms;
	}*/


}//scene