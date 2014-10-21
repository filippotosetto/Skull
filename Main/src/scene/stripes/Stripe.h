//
//  Stripe.h
//  Main
//
//  Created by Filippo Tosetto on 21/10/2014.
//
//

#ifndef __Main__Stripe__
#define __Main__Stripe__

#include "ofMain.h"

class Stripe {
    
public:
    Stripe(float _yPosition);
    
    void draw();
    void setHeight(float _height) { height = _height; }
    
private:
    float yPosition;
    float width;
    float height;
};

#endif /* defined(__Main__Stripe__) */
