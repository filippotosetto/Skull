#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetFrameRate(60);
    ofBackground(0);

    // fbo
    fbo.allocate(STAGE_WIDTH, STAGE_HEIGHT, GL_RGBA);

    // plane
    plane.set(STAGE_WIDTH, STAGE_HEIGHT, 20, 20);
    plane.resizeToTexture(fbo.getTextureReference());

    AudioManager::init();
    SceneManager::init();
//    Tweenzor::init();

    initGUI();
    initDrags();
    initScenes();

    updateMesh();

}

//--------------------------------------------------------------
void ofApp::update(){

    // update tweens
//    Tweenzor::update(ofGetElapsedTimeMillis());

    // update audio
    AudioManager::update();

    // fbo
    fbo.begin();
	ofClear(0, 0, 0, 0);

    // scene
    if (drawScenes) {
        SceneManager::getCurrentScene()->update();
    }

    fbo.end();

}

//--------------------------------------------------------------
void ofApp::draw(){

    if (drawDistortion) {
        // wireframe
        if (drawWireframe) {
            ofPushStyle();
            ofNoFill();
            ofSetColor(250, 50);
            plane.drawWireframe();
            ofPopStyle();
        }

        // texture
        fbo.getTextureReference().bind();

        ofPushStyle();
        ofFill();
        ofSetColor(255);
        plane.setPosition(STAGE_WIDTH * 0.5, STAGE_HEIGHT * 0.5, 0);
        plane.draw();
        ofPopStyle();

        fbo.getTextureReference().unbind();

        // drags
        for(vector<Drag>::iterator d = drags.begin(); d != drags.end(); ++d) {
            d->draw();
        }
    }
    else fbo.draw(0, 0);

    if (guiVisible) {
        gui.draw();
        SceneManager::getCurrentScene()->gui.draw();
    }

}

//--------------------------------------------------------------
void ofApp::initGUI() {

    string guiPath = "main.xml";
    gui.setup("main", guiPath, UI_SPACE, UI_SPACE);
    gui.add(drawScenes.setup("drawScenes", true));
    gui.add(drawWireframe.setup("drawWireframe", false));
    gui.add(drawDistortion.setup("drawDistortion", false));
    gui.loadFromFile(guiPath);

}

//--------------------------------------------------------------
void ofApp::initDrags() {

    ofxXmlSettings settings;
    settings.loadFile("settings.xml");

    ofMesh & mesh = plane.getMesh();
    int cols = plane.getNumColumns();
    int rows = plane.getNumRows();
    ofPoint center = ofPoint(STAGE_WIDTH * 0.5, STAGE_HEIGHT * 0.5);

    ofPoint vTL = mesh.getVertex(0);
    ofPoint vTR = mesh.getVertex(cols - 1);
    ofPoint vBL = mesh.getVertex(cols * rows - cols);
    ofPoint vBR = mesh.getVertex(cols * rows - 1);

    ofPoint dTL = ofPoint(settings.getValue("settings:TLx", vTL.x), settings.getValue("settings:TLy", vTL.y));
    ofPoint dTR = ofPoint(settings.getValue("settings:TRx", vTR.x), settings.getValue("settings:TRy", vTR.y));
    ofPoint dBL = ofPoint(settings.getValue("settings:BLx", vBL.x), settings.getValue("settings:BLy", vBL.y));
    ofPoint dBR = ofPoint(settings.getValue("settings:BRx", vBR.x), settings.getValue("settings:BRy", vBR.y));

    drags.push_back(Drag(dTL + center));
    drags.push_back(Drag(dTR + center));
    drags.push_back(Drag(dBL + center));
    drags.push_back(Drag(dBR + center));

}

//--------------------------------------------------------------
void ofApp::initScenes() {

    SceneManager::add(new AbstractScene(SceneManager::getNum(), "abstract"));
    SceneManager::navto(0);

}

//--------------------------------------------------------------
ofPoint ofApp::lerpPoint(ofPoint start, ofPoint end, float amt) {

    return start + amt * (end - start);

}

//--------------------------------------------------------------
void ofApp::updateMesh() {

    ofMesh & mesh = plane.getMesh();

    int cols = plane.getNumColumns();
    int rows = plane.getNumRows();
    ofPoint center = ofPoint(STAGE_WIDTH * 0.5, STAGE_HEIGHT * 0.5);

    ofPoint vTL = drags.at(0).pos - center;
    ofPoint vTR = drags.at(1).pos - center;
    ofPoint vBL = drags.at(2).pos - center;
    ofPoint vBR = drags.at(3).pos - center;

    for (int i = 0; i < cols; i++) {
        float amt = float(i) / (cols - 1);
        ofPoint vT = lerpPoint(vTL, vTR, amt);
        ofPoint vB = lerpPoint(vBL, vBR, amt);

        for (int j = 0; j < rows; j++) {
            float amt = float(j) / (rows - 1);
            ofPoint v = lerpPoint(vT, vB, amt);
            mesh.setVertex(i + cols * j, v);
        }
    }
}

//--------------------------------------------------------------
void ofApp::saveSettings() {

    ofPoint center = ofPoint(STAGE_WIDTH * 0.5, STAGE_HEIGHT * 0.5);
    ofPoint vTL = drags.at(0).pos - center;
    ofPoint vTR = drags.at(1).pos - center;
    ofPoint vBL = drags.at(2).pos - center;
    ofPoint vBR = drags.at(3).pos - center;

    ofxXmlSettings settings;
    settings.setValue("settings:TLx", vTL.x);
    settings.setValue("settings:TLy", vTL.y);
    settings.setValue("settings:TRx", vTR.x);
    settings.setValue("settings:TRy", vTR.y);
    settings.setValue("settings:BLx", vBL.x);
    settings.setValue("settings:BLy", vBL.y);
    settings.setValue("settings:BRx", vBR.x);
    settings.setValue("settings:BRy", vBR.y);
    settings.saveFile("settings.xml");

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    switch (key) {

        case OF_KEY_RIGHT: {
            SceneManager::next();
            break;
        }

        case OF_KEY_LEFT: {
            SceneManager::prev();
            break;
        }

        case 'g': {
            guiVisible = !guiVisible;
            break;
        }

    }

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {

    if (!drawDistortion) return;

    for (vector<Drag>::iterator d = drags.begin(); d != drags.end(); ++d) {
        float dx = ofGetMouseX() - d->pos.x;
        float dy = ofGetMouseY() - d->pos.y;
        float dd = dx * dx + dy * dy;

        if (dd < Drag::HIT_RADIUS_SQ) d->mouseOver();
        else if (d->over) d->mouseOut();
    }

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

    if (!drawDistortion) return;

    for (vector<Drag>::iterator d = drags.begin(); d != drags.end(); ++d) {
        if (d->down) {
            d->mouseMoved();
            updateMesh();
            return;
        }
    }

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

    if (!drawDistortion) return;

    for (vector<Drag>::iterator d = drags.begin(); d != drags.end(); ++d) {
        float dx = ofGetMouseX() - d->pos.x;
        float dy = ofGetMouseY() - d->pos.y;
        float dd = dx * dx + dy * dy;

        if (dd < Drag::HIT_RADIUS_SQ) d->mousePressed();
    }

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

    if (!drawDistortion) return;

    for (vector<Drag>::iterator d = drags.begin(); d != drags.end(); ++d) {
        if (d->down) {
            d->mouseReleased();
            saveSettings();
        }
    }

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
