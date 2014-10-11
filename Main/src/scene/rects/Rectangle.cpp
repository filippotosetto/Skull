//
//  Rectangle.cpp
//  Main
//
//  Created by Filippo Tosetto on 10/10/2014.
//
//

#include "Rectangle.h"

Rectangle::Rectangle(ofVec2f _location) {
    location = _location;    
    width = ofRandom(1, 30);
}

void Rectangle::draw() {
    
    glPushMatrix();

        glTranslatef(ofGetWidth() / 2, ofGetHeight() / 2,0);
        glRotatef(rotation + 45,0,0,1);
    
        ofSetColor(255);
        ofRect(location.x, location.y, 10, width, height);
    
    glPopMatrix();
}