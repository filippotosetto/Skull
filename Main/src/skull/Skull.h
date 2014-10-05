#pragma once

#include "ofMain.h"
#include "ofAppDefines.h"
#include "ofxAssimpModelLoader.h"

class Skull {
    public:
        Skull();

        void setup();
        void update();
        void draw();

        ofxAssimpModelLoader model;
        ofLight	light;
};
