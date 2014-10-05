//
//  Circle.h
//  Main
//
//  Created by Filippo Tosetto on 01/10/2014.
//
//

#ifndef __swissGrid__Circle__
#define __swissGrid__Circle__

#include "ofMain.h"

class Circle {
    
    public:
        Circle(ofVec2f _location);

        void draw();
        void setRadius(float _radius) { radius = _radius; }
    
    private:
        ofVec2f location;
        float radius;
        float maxRadius;
};

#endif /* defined(__swissGrid__Circle__) */
