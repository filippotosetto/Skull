//
//  Circle.cpp
//  Main
//
//  Created by Filippo Tosetto on 01/10/2014.
//
//

#include "Circle.h"

Circle::Circle(ofVec2f _location) {
    location = _location;
    maxRadius = radius = 20;
}

void Circle::draw() {
    
    //check outer circle radius
    maxRadius = (radius > maxRadius) ? radius : maxRadius - 0.5;

    
    ofPushStyle();

    ofSetCircleResolution(100);
    
    // outer circle
    ofSetColor(70, 26, 26);
    ofCircle(location.x, location.y, maxRadius);
    
    // inner circle
    ofSetColor(107, 107, 70);
    ofCircle(location.x, location.y, radius);
    
    ofPopStyle();
}
