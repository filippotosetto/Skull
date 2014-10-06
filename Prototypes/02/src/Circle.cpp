//
//  Circle.cpp
//  swissGrid
//
//  Created by Filippo Tosetto on 01/10/2014.
//
//

#include "Circle.h"

Circle::Circle(ofVec2f _location) {
    location = _location;
    radius = 20;
    maxRadius = 0;
}

void Circle::draw() {
    
    if (radius > maxRadius) {
        maxRadius = radius;
    } else {
        maxRadius -= .5;
    }
    
    ofSetCircleResolution(100);
    
    ofSetColor(70, 26, 26);
    ofCircle(location.x, location.y, maxRadius);
    
    ofSetColor(107, 107, 70);
    ofCircle(location.x, location.y, radius);
}
