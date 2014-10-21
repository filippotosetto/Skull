//
//  StripesScene.cpp
//  Main
//
//  Created by Filippo Tosetto on 21/10/2014.
//
//

#include "StripesScene.h"

//--------------------------------------------------------------
StripesScene::StripesScene() {
}

//--------------------------------------------------------------
void StripesScene::setup() {
    
    AbstractScene::setup();
    
    maxStripeHeight = ofGetHeight() / numberOfBins;
    setupStripes();

}

//--------------------------------------------------------------
void StripesScene::update() {
    
    AbstractScene::update();
    
    
    if (isShowing || isHiding) {
        for(int i = 0; i < stripes.size(); i++) {
            Stripe *c = &stripes[i];
            c->setHeight(transitionHeight);
            c->draw();
        }
        return;
    }
    
    // audio data
    float * audioData = new float[numberOfBins];
    AudioManager::getFFT()->getFftPeakData(audioData, numberOfBins);
    
    // if number of circles changed empty the reset it
    if (stripes.size() != numberOfBins) {
        setupStripes();
    }
    
    // draw
    for(int i = 0; i < stripes.size(); i++) {
        Stripe *c = &stripes[i];
        c->setHeight(maxStripeHeight * audioData[i] * .7);
        c->draw();
    }
    
    
    // FFT Debug
    if (showFFTDebug) {
        for(int i=0; i < numberOfBins; i++) {
            float audioValue = audioData[i];
            float height = 50 * audioValue;
            ofRect((5 + 2) * i, ofGetHeight() - height, 5, height);
        }
    }
}

//--------------------------------------------------------------
void StripesScene::hide() {

    AbstractScene::hide();
}

//--------------------------------------------------------------
void StripesScene::show() {

    AbstractScene::show(1000);
    
    Tweenzor::add(&transitionHeight, maxStripeHeight, 0.f, 0.f, 5.f, EASE_OUT_QUART);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&transitionHeight), this, &StripesScene::onStripesSlideInOut);
}


void StripesScene::onStripesSlideInOut(float* arg) {
    Tweenzor::removeCompleteListener(Tweenzor::getTween(&transitionHeight));
}

//--------------------------------------------------------------
void StripesScene::initGUI() {
    
    AbstractScene::initGUI();
    
    gui.add(numberOfBins.setup("Number of bins", 50, 1, 100));
    gui.add(showFFTDebug.setup("Show FFT Debug", false));
    
    gui.loadFromFile("stripes.xml");
}

void StripesScene::setupStripes() {
    maxStripeHeight = ofGetHeight() / numberOfBins;

    stripes.clear();
    
    for(int i=0; i < numberOfBins; i++) {
        Stripe stripe = Stripe(maxStripeHeight * i);
        stripe.draw();
        stripes.push_back(stripe);
    }
}