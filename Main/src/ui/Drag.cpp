#include "Drag.h"

Drag::Drag(ofVec3f _pos) {
    pos = _pos;
    radius = RADIUS + 1;
    alpha = 255;
    lineWidth = 3;
    down = false;
}

//------------------------------------------------------------------
void Drag::draw() {
    ofPushStyle();
    ofSetColor(ofColor(250, 250, 250, alpha));
    ofFill();
    ofCircle(pos.x, pos.y, radius);
    ofPopStyle();

    ofPushStyle();
    ofSetColor(ofColor(250, alpha));
    ofNoFill();
    ofSetLineWidth(lineWidth);
    ofCircle(pos.x, pos.y, radius);
    ofPopStyle();
}

//------------------------------------------------------------------
void Drag::mousePressed(){
    down = true;
}

//------------------------------------------------------------------
void Drag::mouseMoved(){
    pos.x = ofGetMouseX();
    pos.y = ofGetMouseY();
}

//------------------------------------------------------------------
void Drag::mouseReleased(){
    down = false;
}

//------------------------------------------------------------------
void Drag::mouseOver() {
    over = true;
    radius = RADIUS + 1;
    alpha = 200;
    lineWidth = 3;
}

//------------------------------------------------------------------
void Drag::mouseOut() {
    over = false;
    radius = RADIUS;
    alpha = 150;
    lineWidth = 2;
}

