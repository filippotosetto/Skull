//
//  RectsScene.cpp
//  Main
//
//  Created by Filippo Tosetto on 09/10/2014.
//
//

#include "RectsScene.h"


//--------------------------------------------------------------
RectsScene::RectsScene() {
}

//--------------------------------------------------------------
void RectsScene::setup() {
    
    AbstractScene::setup();
    
//    setupCircles();
}

//--------------------------------------------------------------
void RectsScene::update() {
    
    AbstractScene::update();
    

    // audio data
    float * audioData = new float[numberOfBins];
    AudioManager::getFFT()->setMaxDecay(maxDecay);
    AudioManager::getFFT()->setMirrorData(showMirrorData);
    AudioManager::getFFT()->getFftPeakData(audioData, numberOfBins);
    
    // if number of circles changed empty the reset it
    if (rects.size() != numberOfBins) {
        setupRects();
    }
    
    // draw
    for(int i = 0; i < rects.size(); i++) {
        Rectangle *c = &rects[i];
        c->setHeight(maxRectsHeight * audioData[i]);
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
void RectsScene::hide() {
    
    AbstractScene::hide(600);
    
    ofBackground(0);
//    float tx = (STAGE_WIDTH - rect.width) / 2;
//    float tw = (STAGE_WIDTH + rect.width) / 2;
//    Tweenzor::add(&rect.x, rect.x, tx, 0.f, 0.3f, EASE_OUT_QUART);
//    Tweenzor::add(&rect.width, rect.width, tw, 0.f, 0.3f, EASE_OUT_QUART);
//    Tweenzor::addCompleteListener(Tweenzor::getTween(&rect.width), this, &ExampleScene::onRectSlideOut);
    
}

//--------------------------------------------------------------
void RectsScene::show() {
    
    AbstractScene::show(600);
    
//    ofBackground(4, 68, 148);
    
    Tweenzor::add(&_r, 0.f, 4.f, 0.f, 2.f);
    Tweenzor::add(&_g, 0.f, 68.f, 0.f, 2.f);
    Tweenzor::add(&_b, 0.f, 148.f, 0.f, 2.f);

    //    float tx = (STAGE_WIDTH - rect.width) / 2;
    //    float tw = (STAGE_WIDTH + rect.width) / 2;
    //    Tweenzor::add(&rect.x, rect.x, tx, 0.f, 0.3f, EASE_OUT_QUART);
    //    Tweenzor::add(&rect.width, rect.width, tw, 0.f, 0.3f, EASE_OUT_QUART);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&_r), this, &RectsScene::onBackroundShow);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&_g), this, &RectsScene::onBackroundShow);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&_b), this, &RectsScene::onBackroundShow);

}


void RectsScene::onBackroundShow(float* arg) {
    
//    float tw = rectSize;
//    float tx = (STAGE_WIDTH - tw) / 2;
//    Tweenzor::add(&rect.width, rect.width, tw, 0.f, 0.3f, EASE_IN_OUT_QUART);
//    Tweenzor::add(&rect.x, rect.x, tx, 0.f, 0.3f, EASE_IN_OUT_QUART);
    Tweenzor::removeCompleteListener(Tweenzor::getTween(&_r));
    Tweenzor::removeCompleteListener(Tweenzor::getTween(&_g));
    Tweenzor::removeCompleteListener(Tweenzor::getTween(&_b));
    
}

//--------------------------------------------------------------
void RectsScene::initGUI() {
    
    AbstractScene::initGUI();
    
    gui.add(numberOfBins.setup("Number of bins", 20, 1, 50));
    gui.add(maxRectsHeight.setup("Max Rects Height", 300, 10, 350));
    gui.add(showFFTDebug.setup("Show FFT Debug", false));
    
    gui.add(showMirrorData.setup("Show Mirror Data", false));
    gui.add(maxDecay.setup("Max Decay", 0.5 , 0.1, 1 ));
    
    gui.loadFromFile("rects.xml");
}

void RectsScene::setupRects() {
    rects.clear();
    for(int i=0; i < numberOfBins; i++) {
        float locationStep = 50;
        ofVec2f location = ofVec2f(ofRandom(-locationStep, locationStep), ofRandom(0, locationStep));
        Rectangle rect = Rectangle(location);
        rect.setRotation(i % 4 * 90);
        rect.draw();
        rects.push_back(rect);
        
    }
}


