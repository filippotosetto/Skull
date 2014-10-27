#include "Skull.h"

//--------------------------------------------------------------
Skull::Skull() {

}

//--------------------------------------------------------------
void Skull::setup() {

    model.loadModel("skull.dae", true);
    model.setPosition(STAGE_WIDTH * 0.5, STAGE_HEIGHT * 0.55 , 0);
}

//--------------------------------------------------------------
void Skull::update() {

    model.update();

}

//--------------------------------------------------------------
void Skull::draw() {

    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
    ofEnableDepthTest();
    glShadeModel(GL_SMOOTH);
    light.enable();
    ofEnableSeparateSpecularLight();

//    ofPushMatrix();
//    ofTranslate(model.getPosition().x, model.getPosition().y, 0);
//    ofRotate(-mouseX, 0, 1, 0);
//    ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);
    ofPushStyle();

    if(delegate) {
        ofColor newColor = delegate->getSkullColor();
        ofSetColor(newColor);
    }
    
    model.drawFaces();
    ofPopStyle();
//    ofPopMatrix();


    // No idea why we need to disable everything after drawing faces
    // RE: it is like PushMatrix / PopMatrix. If you don't disable, it will be enabled on the next iteration.
    ofDisableDepthTest();
    light.disable();
    ofDisableLighting();
    ofDisableSeparateSpecularLight();
}

