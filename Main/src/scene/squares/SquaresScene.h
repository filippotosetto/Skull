//
//  SquaresScene.h
//  Main
//
//  Created by Filippo Tosetto on 23/10/2014.
//
//

#ifndef __Main__SquaresScene__
#define __Main__SquaresScene__


#include "../abstract/AbstractScene.h"
#include "ofxGui.h"
#include "Square.h"

class SquaresScene : public AbstractScene {
    
public:
    SquaresScene();
    SquaresScene(int index, string name):AbstractScene(index, name) {}
    
    void setup();
    void update();
    void hide();
    void show();
    
    void initGUI();
    
private:
    vector<Square> rects;
    
    ofxSlider<int> numberOfBins;
    ofxSlider<int> maxRectsHeight;
    ofxToggle showFFTDebug;
    
    ofxSlider<float> maxDecay;
    ofxToggle showMirrorData;
    
    void setupSquares();
    
};

#endif /* defined(__Main__SquaresScene__) */
