#include "ExampleScene.h"

//--------------------------------------------------------------
ExampleScene::ExampleScene() {
}

//--------------------------------------------------------------
void ExampleScene::setup() {

    AbstractScene::setup();

    rect.set(0.f, 0.f, rectSize, rectSize);

}

//--------------------------------------------------------------
void ExampleScene::update() {

    AbstractScene::update();

    // show
    if (isShowing) {
        ofDrawBitmapString("EXAMPLE SHOWING", 10, STAGE_HEIGHT - 20);

        ofPushStyle();
        ofSetColor(ofColor::white);
        ofRect(rect);
        ofPopStyle();
        return;
    }

    // hide
    if (isHiding) {
        ofDrawBitmapString("EXAMPLE HIDING", 10, STAGE_HEIGHT - 20);

        ofPushStyle();
        ofSetColor(ofColor::white);
        ofRect(rect);
        ofPopStyle();
        return;
    }

    // update
    ofDrawBitmapString("NORMAL UPDATE", 10, STAGE_HEIGHT - 20);

    // audio data
    int numData = 10;
    float * audioData = new float[numData];
    AudioManager::getFFT()->getFftPeakData(audioData, numData);

    // draw
    float variation = 100;
    rect.width = rectSize + audioData[0] * variation;
    rect.height = rectSize; // + audioData[1] * variation;
    rect.x = (STAGE_WIDTH - rect.width) / 2;
    rect.y = (STAGE_HEIGHT - rect.height) / 5  * 4;

    skull->light1Position.z = audioData[2] * 600 - 300;

    if (AudioManager::getKick()) skull->getModel()->setRotation(0, ofRandom(-20, 20), 1, 0, 0);

    ofPushStyle();
    ofSetColor(ofColor::white);
    int w = OFX_FFT_WIDTH;
    int h = 200;
    int x = 20;
    int y = ofGetHeight() - h - 20;
    AudioManager::getFFT()->draw(x, y, w, h);
    ofPopStyle();

    ofPushStyle();
    ofSetColor(ofColor::white);
    ofRect(rect);
    ofPopStyle();

}

//--------------------------------------------------------------
void ExampleScene::show() {

    AbstractScene::show(800);

    rect.x = 0.f;
    rect.y = (STAGE_HEIGHT - rect.height) / 5  * 4;
    rect.width = rectSize;
    float tw = (STAGE_WIDTH + rect.width) / 2;
    Tweenzor::add(&rect.width, rect.width, tw, 0.f, 0.5f, EASE_OUT_QUART);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&rect.width), this, &ExampleScene::onRectSlideIn);

}

//--------------------------------------------------------------
void ExampleScene::hide() {

    AbstractScene::hide(600);

    float tx = (STAGE_WIDTH - rect.width) / 2;
    float tw = (STAGE_WIDTH + rect.width) / 2;
    Tweenzor::add(&rect.x, rect.x, tx, 0.f, 0.3f, EASE_OUT_QUART);
    Tweenzor::add(&rect.width, rect.width, tw, 0.f, 0.3f, EASE_OUT_QUART);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&rect.width), this, &ExampleScene::onRectSlideOut);

}

//--------------------------------------------------------------
void ExampleScene::initGUI() {

    AbstractScene::initGUI();

}

//--------------------------------------------------------------
void ExampleScene::onRectSlideIn(float* arg) {

    float tw = rectSize;
    float tx = (STAGE_WIDTH - tw) / 2;
    Tweenzor::add(&rect.width, rect.width, tw, 0.f, 0.3f, EASE_IN_OUT_QUART);
    Tweenzor::add(&rect.x, rect.x, tx, 0.f, 0.3f, EASE_IN_OUT_QUART);
    Tweenzor::removeCompleteListener(Tweenzor::getTween(&rect.width));

}

//--------------------------------------------------------------
void ExampleScene::onRectSlideOut(float* arg) {

    float tx = STAGE_WIDTH;
    Tweenzor::add(&rect.x, rect.x, tx, 0.f, 0.3f, EASE_IN_OUT_QUART);
    Tweenzor::removeCompleteListener(Tweenzor::getTween(&rect.width));

}

