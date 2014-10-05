//
//  CirclesScene.cpp
//  Main
//
//  Created by Filippo Tosetto on 05/10/2014.
//
//

#include "CirclesScene.h"

//--------------------------------------------------------------
CirclesScene::CirclesScene() {
}

//--------------------------------------------------------------
void CirclesScene::setup() {
    
    AbstractScene::setup();

    setupCircles();
}

//--------------------------------------------------------------
void CirclesScene::update() {
    
    AbstractScene::update();
    
    // audio data
    float * audioData = new float[numberOfBins];
    AudioManager::getFFT()->getFftPeakData(audioData, numberOfBins);
    
    // if number of circles changed empty the reset it
    if (circles.size() != numberOfBins) {
        setupCircles();
    }
    
    // draw
    for(int i = 0; i < circles.size(); i++) {
        Circle *c = &circles[i];
        c->setRadius(maxCircleRadius * audioData[i]);
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
void CirclesScene::initGUI() {
    
    AbstractScene::initGUI();
    
    gui.add(numberOfBins.setup("Number of bins", 20, 1, 50));
    gui.add(maxCircleRadius.setup("Max Circle Radius", 50, 10, 150));
    gui.add(showFFTDebug.setup("Show FFT Debug", true));
    
    gui.loadFromFile("circles.xml");
}


//--------------------------------------------------------------
void CirclesScene::setupCircles() {
    circles.clear();
    for(int i=0; i < numberOfBins; i++) {
        ofVec2f location = ofVec2f(ofRandom(maxCircleRadius, ofGetWidth() - maxCircleRadius), ofRandom(maxCircleRadius, ofGetHeight() - maxCircleRadius));
        Circle c = Circle(location);
        c.draw();
        circles.push_back(c);
    }
}


