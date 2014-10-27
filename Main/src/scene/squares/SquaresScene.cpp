//
//  SquaresScene.cpp
//  Main
//
//  Created by Filippo Tosetto on 23/10/2014.
//
//

#include "SquaresScene.h"



//--------------------------------------------------------------
SquaresScene::SquaresScene() {
}

//--------------------------------------------------------------
void SquaresScene::setup() {
    
    AbstractScene::setup();
    
    //    setupCircles();
}

//--------------------------------------------------------------
void SquaresScene::update() {
    
    AbstractScene::update();
    
    
//    if (isShowing || isHiding) {
//        return;
//    }
    
    // audio data
    float * audioData = new float[numberOfBins];
    AudioManager::getFFT()->setMaxDecay(maxDecay);
    AudioManager::getFFT()->setMirrorData(showMirrorData);
    AudioManager::getFFT()->getFftPeakData(audioData, numberOfBins);
    
    // if number of circles changed empty the reset it
    if (rects.size() != numberOfBins) {
        setupSquares();
    }
    
    // draw
    for(int i = 0; i < rects.size(); i++) {
        Square *c = &rects[i];
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
void SquaresScene::hide() {
    
    AbstractScene::hide();
//    AbstractScene::hide(2000);
//    
//    Tweenzor::add(&_r, 4.f, 0.f, 0.f, 5.f, EASE_OUT_QUART);
//    Tweenzor::add(&_g, 68.f, 0.f, 0.f, 5.f, EASE_OUT_QUART);
//    Tweenzor::add(&_b, 148.f, 0.f, 0.f, 5.f, EASE_OUT_QUART);
//    
//    Tweenzor::addCompleteListener(Tweenzor::getTween(&_r), this, &RectsScene::onBackroundChange);
//    Tweenzor::addCompleteListener(Tweenzor::getTween(&_g), this, &RectsScene::onBackroundChange);
//    Tweenzor::addCompleteListener(Tweenzor::getTween(&_b), this, &RectsScene::onBackroundChange);
}

//--------------------------------------------------------------
void SquaresScene::show() {
    
    AbstractScene::show();
//    AbstractScene::show(2000);
//
//    Tweenzor::add(&_r, 0.f, 4.f, 0.f, 5.f, EASE_OUT_QUART);
//    Tweenzor::add(&_g, 0.f, 68.f, 0.f, 5.f, EASE_OUT_QUART);
//    Tweenzor::add(&_b, 0.f, 148.f, 0.f, 5.f, EASE_OUT_QUART);
//    
//    Tweenzor::addCompleteListener(Tweenzor::getTween(&_r), this, &RectsScene::onBackroundChange);
//    Tweenzor::addCompleteListener(Tweenzor::getTween(&_g), this, &RectsScene::onBackroundChange);
//    Tweenzor::addCompleteListener(Tweenzor::getTween(&_b), this, &RectsScene::onBackroundChange);
    
}
//--------------------------------------------------------------
void SquaresScene::initGUI() {
    
    AbstractScene::initGUI();
    
    gui.add(numberOfBins.setup("Number of bins", 20, 1, 50));
    gui.add(maxRectsHeight.setup("Max Rects Height", 300, 10, 350));
    gui.add(showFFTDebug.setup("Show FFT Debug", false));
    
    gui.add(showMirrorData.setup("Show Mirror Data", false));
    gui.add(maxDecay.setup("Max Decay", 0.5 , 0.1, 1 ));
    
    gui.loadFromFile("rects.xml");
}

void SquaresScene::setupSquares() {
    rects.clear();
    for(int i=0; i < numberOfBins; i++) {
        float locationStep = 50;
        ofVec2f location = ofVec2f(ofRandom(-locationStep, locationStep), ofRandom(0, locationStep));
//        Square rect = Square(location);
//        rect.setRotation(i % 4 * 90);
//        rect.draw();
//        rects.push_back(rect);
        
    }
}