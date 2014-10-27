#pragma once

#include "ofMain.h"
#include "ofAppDefines.h"
#include "ofxAssimpModelLoader.h"
#include "SkullDelegate.h"

class Skull {
    public:
        Skull();

        void setup();
        void update();
        void draw();

        ofxAssimpModelLoader model;
        ofLight	light;
    
        SkullDelegate *delegate;
    
};
