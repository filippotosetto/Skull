//
//  CirclesScene.h
//  Main
//
//  Created by Filippo Tosetto on 05/10/2014.
//
//

#ifndef __Main__CirclesScene__
#define __Main__CirclesScene__

#include "../abstract/AbstractScene.h"
#include "Circle.h"
#include "ofxGui.h"

class CirclesScene : public AbstractScene {

public:
    CirclesScene();
    CirclesScene(int index, string name, Skull* skull):AbstractScene(index, name, skull) {}

    void setup();
    void update();

    void initGUI();

private:
    vector<Circle> circles;

    ofxSlider<int> numberOfBins;
    ofxSlider<int> maxCircleRadius;
    ofxToggle showFFTDebug;

    void setupCircles();
};
#endif /* defined(__Main__CirclesScene__) */
