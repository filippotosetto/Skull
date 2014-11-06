#include "AbstractScene.h"

//--------------------------------------------------------------
AbstractScene::AbstractScene() {

}

//--------------------------------------------------------------
AbstractScene::AbstractScene(int _index, string _name, Skull* _skull) {

    index = _index;
    name = _name;
    skull = _skull;

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

    show(0);

}

//--------------------------------------------------------------
void AbstractScene::show(float millis) {

    skull->loadSettings(name);

    if (millis <= 0) {
        showComplete();
        return;
    }

    ofAddListener(timer.TIMER_REACHED, (AbstractScene*)this, &AbstractScene::showComplete);
    timer.setup(millis, false);

}

//--------------------------------------------------------------
void AbstractScene::hide() {

    hide(0);

}

//--------------------------------------------------------------
void AbstractScene::hide(float millis) {

    if (millis <= 0) {
        hideComplete();
        return;
    }

    ofAddListener(timer.TIMER_REACHED, (AbstractScene*)this, &AbstractScene::hideComplete);
    timer.setup(millis, false);

}


//--------------------------------------------------------------
void AbstractScene::showComplete(ofEventArgs &e) {

    ofRemoveListener(timer.TIMER_REACHED, this, &AbstractScene::showComplete);
    showComplete();

}

//--------------------------------------------------------------
void AbstractScene::hideComplete(ofEventArgs &e) {

    ofRemoveListener(timer.TIMER_REACHED, this, &AbstractScene::hideComplete);
    hideComplete();

}

//--------------------------------------------------------------
void AbstractScene::showComplete() {

    ofNotifyEvent(onShowComplete, isShowing);

}

//--------------------------------------------------------------
void AbstractScene::hideComplete() {

    ofNotifyEvent(onHideComplete, isHiding);

}


//--------------------------------------------------------------
void AbstractScene::update() {

    // if (isShowing)

    // if (isHiding)

    // normal update

}


//--------------------------------------------------------------
void AbstractScene::exit() {

}
