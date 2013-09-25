#include "Node.h"

namespace scene{


	/// <summary>
	/// Initializes a new instance of the <see cref="Node"/> class.
	/// Only copies node name
	/// </summary>
	/// <param name="n">The n.</param>
	Node::Node(const Node &n){
		this->name=n.name;
		//////
	}

	Node::~Node(){
		delete[] trasnforms;
	}


}//scene