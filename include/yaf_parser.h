#ifndef _YAF_PARSER
#define _YAF_PARSER

#include "tinyxml2.h"
#include <iostream>
#include <string>

namespace yaf_parser{

	using namespace std;
	using namespace tinyxml2;

	enum ERRORS { globals_error = 1, cameras_error, file_nf};
	enum node_i {
		GLOBALS,CAMERAS,LIGHTNING,PERSPECTIVE,ORTHO
	};

	class Parser{
	public:

		/* Initial method for parsing
		** return 0 success, or above means error */
		int start();



	private:
		bool globals(XMLElement *elem);
		bool cameras(XMLElement *elem);
		bool lightning(XMLElement *elem);
		bool textures(XMLElement *elem);
		bool appearances(XMLElement *elem);
		bool graph(XMLElement *elem);
	};



}//yaf_parser

#endif