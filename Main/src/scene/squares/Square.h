//
//  Square.h
//  Main
//
//  Created by Filippo Tosetto on 23/10/2014.
//
//

#ifndef __Main__Square__
#define __Main__Square__

#include "ofMain.h"

class Square {
    
public:
    Square(ofVec2f _location, float _width);
    
    void draw();
    void setHeight(float _height) { height = _height; }
    
private:
    ofVec2f location;
    float width;
    float height;
};

#endif /* defined(__Main__Square__) */
