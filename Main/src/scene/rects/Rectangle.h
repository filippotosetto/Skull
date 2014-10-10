//
//  Rectangle.h
//  Main
//
//  Created by Filippo Tosetto on 10/10/2014.
//
//

#ifndef __Main__Rectangle__
#define __Main__Rectangle__

#include "ofMain.h"

class Rectangle {
    
public:
    Rectangle(ofVec2f _location);
    
    void draw();
    void setHeight(float _height) { height = _height; }
    void setRotation(float _rotation) { rotation = _rotation; }
    
private:
    ofVec2f location;
    float width;
    float height;
    float rotation;
};


#endif /* defined(__Main__Rectangle__) */
