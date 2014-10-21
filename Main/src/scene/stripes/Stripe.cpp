//
//  Stripe.cpp
//  Main
//
//  Created by Filippo Tosetto on 21/10/2014.
//
//

#include "Stripe.h"

Stripe::Stripe(float _yPosition) {
    yPosition = _yPosition;
    height = 0;
}

void Stripe::draw() {

    ofPushStyle();
    
    ofSetColor(ofColor::red);
    ofRect(0, yPosition, ofGetWidth(), height);
    
    ofPopStyle();
}