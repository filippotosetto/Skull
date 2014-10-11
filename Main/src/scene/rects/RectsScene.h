//
//  RectsScene.h
//  Main
//
//  Created by Filippo Tosetto on 09/10/2014.
//
//

#ifndef __Main__RectsScene__
#define __Main__RectsScene__

#include "../abstract/AbstractScene.h"
#include "ofxGui.h"
#include "Rectangle.h"

class RectsScene : public AbstractScene {
    
public:
    RectsScene();
    RectsScene(int index, string name):AbstractScene(index, name) {}
    
    void setup();
    void update();
    void hide();
    void show();
    
    void initGUI();
    
private:
    vector<Rectangle> rects;
    
    ofxSlider<int> numberOfBins;
    ofxSlider<int> maxRectsHeight;
    ofxToggle showFFTDebug;

    ofxSlider<float> maxDecay;
    ofxToggle showMirrorData;
    
    void setupRects();
    
    float _r;
    float _g;
    float _b;
    
    void onBackroundShow(float* arg);
};
#endif /* defined(__Main__RectsScene__) */
