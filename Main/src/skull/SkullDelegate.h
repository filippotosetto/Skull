//
//  SkullDelegate.h
//  Main
//
//  Created by Filippo Tosetto on 25/10/2014.
//
//

#ifndef Main_SkullDelegate_h
#define Main_SkullDelegate_h

#include "ofMain.h"

class SkullDelegate {
public:
    
    // the default implementation makes this function optional
    // to make the implementation mandatory for the subclass remove {} and add = 0
    virtual ofColor getSkullColor() { return NULL; };
};

#endif
