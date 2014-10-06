#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(50, 0);
    
    // 3D model
    model.loadModel("skull-01.dae", true);
    model.setPosition(ofGetWidth() * 0.5, ofGetHeight() * 0.5 , -300);

    
    // fbo
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGBA);


    // fft
    fftLive.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    // fft
    fftLive.update();
    fftLive.getFftPeakData(audioData, numOfBuckets);
    
    
    // fbo
    fbo.begin();
    ofClear(0, 0, 0, 0);

    ofPushStyle();
    if (circles.size() == 0) {
        for(int i=0; i < numOfBuckets; i++) {
            ofVec2f location = ofVec2f(ofRandom(100, ofGetWidth() - 100), ofRandom(100, ofGetHeight() - 100));
            Circle c = Circle(location);
            c.draw();
            circles.push_back(c);
        }
    } else {
        for(int i=0; i < numOfBuckets; i++) {
            Circle *c = &circles[i];
            c->radius = 100 * audioData[i];
            c->draw();
        }
    }

    ofPopStyle();
    fbo.end();
    
    
    // 3D model
    model.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // draw fbo
    fbo.draw(0, 0);

    
    // 3D model
    ofEnableBlendMode(OF_BLENDMODE_ALPHA);

    ofEnableDepthTest();

    glShadeModel(GL_SMOOTH);
    light.enable();
    ofEnableSeparateSpecularLight();

    bindFBOTexture();

    model.drawFaces();

    unbindFBOTexture();

    ofDisableDepthTest();
    light.disable();
    ofDisableLighting();
    ofDisableSeparateSpecularLight();

}



//--------------------------------------------------------------
// Creates a texture from the fbo object
void ofApp::bindFBOTexture() {
    ofTexture &tex = fbo.getTextureReference();
    tex.bind();
    
    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();
    
    ofTextureData texData = tex.getTextureData();
    if(texData.textureTarget == GL_TEXTURE_RECTANGLE_ARB) {
        glScalef(tex.getWidth(), tex.getHeight(), 1.0f);
    } else {
        glScalef(tex.getWidth() / texData.tex_w, tex.getHeight() / texData.tex_h, 1.0f);
    }
    
    glMatrixMode(GL_MODELVIEW);
}

void ofApp::unbindFBOTexture() {
    fbo.getTextureReference().unbind();
    
    glMatrixMode(GL_TEXTURE);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}



//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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
