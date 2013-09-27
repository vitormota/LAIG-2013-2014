//
//  Transform.h
//  LAIG - P1
//
//  Created by Maria Araújo on 27/09/13.
//  Copyright (c) 2013 me. All rights reserved.
//

#ifndef __LAIG___P1__Transform__
#define __LAIG___P1__Transform__

#include <iostream>
#include <string>
using std::string;

class Transform{
    
private:
    string name;
    
public:
    Transform(string name);
    ~Transform();
    // TODO : Falta matrix da transformacao e criar com herança as classes translate, rotate e scale
    
};

#endif /* defined(__LAIG___P1__Transform__) */
