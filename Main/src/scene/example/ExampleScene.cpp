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

    // hode
    if (isHiding) {
        ofDrawBitmapString("EXAMPLE HIDING", 20, 200);
        return;
    }

    // update
    ofDrawBitmapString("NORMAL UPDATE", 20, 200);

}

//--------------------------------------------------------------
void ExampleScene::show() {

    ofAddListener(timer.TIMER_REACHED, (AbstractScene*)this, &AbstractScene::showComplete);
    timer.setup(2000, false);

}

//--------------------------------------------------------------
void ExampleScene::hide() {

    ofAddListener(timer.TIMER_REACHED, (AbstractScene*)this, &AbstractScene::hideComplete);
    timer.setup(2000, false);

}

//--------------------------------------------------------------
void ExampleScene::initGUI() {

    AbstractScene::initGUI();

}
