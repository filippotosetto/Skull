#include "AbstractScene.h"

//--------------------------------------------------------------
AbstractScene::AbstractScene() {

}

//--------------------------------------------------------------
AbstractScene::AbstractScene(int _index, string _name) {

    index = _index;
    name = _name;

}

//--------------------------------------------------------------
void AbstractScene::setup() {

    initGUI();

}

//--------------------------------------------------------------
void AbstractScene::initGUI() {

    vector<string> strs = ofSplitString(name, " ");
    string n = ofToLower(strs[0]);

    string guiPath = n + ".xml";
    gui.setup(n, guiPath, UI_LENGTH + UI_SPACE * 2, UI_SPACE);

}

//--------------------------------------------------------------
void AbstractScene::show() {

}

//--------------------------------------------------------------
void AbstractScene::hide() {

}

//--------------------------------------------------------------
void AbstractScene::update() {

}

