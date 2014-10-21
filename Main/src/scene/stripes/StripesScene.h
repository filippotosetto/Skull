//
//  StripesScene.h
//  Main
//
//  Created by Filippo Tosetto on 21/10/2014.
//
//

#ifndef __Main__StripesScene__
#define __Main__StripesScene__

#include "../abstract/AbstractScene.h"
#include "ofxGui.h"
#include "Stripe.h"

class StripesScene : public AbstractScene {
    
public:
    StripesScene();
    StripesScene(int index, string name):AbstractScene(index, name) {}
    
    void setup();
    void update();
    void hide();
    void show();
    
    void initGUI();
    
private:
    
    float transitionHeight;
    float maxStripeHeight;
    
    vector<Stripe> stripes;
    
    ofxSlider<int> numberOfBins;
    ofxToggle showFFTDebug;
    
    void setupStripes();
    
    void onStripesSlideInOut(float* arg);
};


#endif /* defined(__Main__StripesScene__) */
