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

    showComplete();

    // use in subclass for a transition
    // ofAddListener(timer.TIMER_REACHED, (AbstractScene*)this, &AbstractScene::showComplete);
    // timer.setup(2000, false);

}

//--------------------------------------------------------------
void AbstractScene::hide() {

    hideComplete();

    // use in subclass for a transition
    // ofAddListener(timer.TIMER_REACHED, (AbstractScene*)this, &AbstractScene::hideComplete);
    // timer.setup(2000, false);
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

