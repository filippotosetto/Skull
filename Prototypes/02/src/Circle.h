//
//  Circle.h
//  swissGrid
//
//  Created by Filippo Tosetto on 01/10/2014.
//
//

#ifndef __swissGrid__Circle__
#define __swissGrid__Circle__

#include "ofMain.h"

class Circle {
public:
    ofVec2f location;
    float radius;
    
    Circle(ofVec2f _location);

    void draw();
    
private:
    float maxRadius;
};

#endif /* defined(__swissGrid__Circle__) */
