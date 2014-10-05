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