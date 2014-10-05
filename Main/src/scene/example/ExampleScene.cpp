#include "ExampleScene.h"

//--------------------------------------------------------------
ExampleScene::ExampleScene() {
}

//--------------------------------------------------------------
void ExampleScene::setup() {

    AbstractScene::setup();

}

//--------------------------------------------------------------
void ExampleScene::update() {

    AbstractScene::update();

    // show
    if (isShowing) {
        ofDrawBitmapString("EXAMPLE SHOWING", 20, 200);
        return;
    }

    // hide
    if (isHiding) {
        ofDrawBitmapString("EXAMPLE HIDING", 20, 200);
        return;
    }

    // update
    ofDrawBitmapString("NORMAL UPDATE", 20, 200);

    // audio data
    int numData = 10;
    float * audioData = new float[numData];
    AudioManager::getFFT()->getFftPeakData(audioData, numData);

    // draw
    float radius = 20;
    float variation = 100;
    float w = radius + audioData[0] * variation;
    float h = radius + audioData[1] * variation;
    float x = (STAGE_WIDTH - w) / 2;
    float y = (STAGE_HEIGHT - h) / 2;

    ofPushStyle();
    ofSetColor(ofColor::white);
    ofRect(x, y, w, h);
    ofPopStyle();

}

//--------------------------------------------------------------
void ExampleScene::show() {

    AbstractScene::show(2000);

}

//--------------------------------------------------------------
void ExampleScene::hide() {

    AbstractScene::hide(2000);

}

//--------------------------------------------------------------
void ExampleScene::initGUI() {

    AbstractScene::initGUI();

}
