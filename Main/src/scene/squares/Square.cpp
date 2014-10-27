//
//  Square.cpp
//  Main
//
//  Created by Filippo Tosetto on 23/10/2014.
//
//

#include "Square.h"

Square::Square(ofVec2f _location, float _width) {
    location = _location;
    width = _width;
}

void Square::draw() {
    
    ofPushStyle();
    
    ofRect(location.x, location.y, width, height);
    
    ofPopStyle();
}
