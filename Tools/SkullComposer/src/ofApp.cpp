#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    radius = 180.f;
	center.set(ofGetWidth()*.5, ofGetHeight()*.5, 0);

    initGUI();
    initShader();
    initCubeMap();
    initModel();
}

//--------------------------------------------------------------
void ofApp::initGUI(){
    font.loadFont(OF_TTF_SANS, 10, false);

    sceneParams.setName("scene");
	sceneParams.add(backgroundColor.set("backgroundColor", ofColor(0, 0, 0), ofColor(0, 0), ofColor(255)));
	sceneParams.add(autoRotate.set("autoRotate", true));

    materialParams.setName("material");
	materialParams.add(emissive.set("emissive", ofColor(127, 0, 0), ofColor(0, 0), ofColor(255)));
	materialParams.add(diffuse.set("diffuse", ofColor(127, 0, 0), ofColor(0, 0), ofColor(255)));
	materialParams.add(specular.set("specular", ofColor(127, 0, 0), ofColor(0, 0), ofColor(255)));
	materialParams.add(shininess.set("shininess", 10, 0, 200));
	materialParams.add(reflectivity.set("reflectivity", 0.5, 0, 1.0));

	renderParams.setName("render");
	renderParams.add(combineLightsMode.set("combineLightsMode", 1, 0, 2));
	renderParams.add(combineEnvironmentMode.set("combineEnvironmentMode", 1, 0, 2));

	lightParams.setName("light");
    lightParams.add(light1Color.set("light1Color", ofColor(127, 0, 0), ofColor(0, 0), ofColor(255)));
    lightParams.add(light2Color.set("light2Color", ofColor(127, 0, 0), ofColor(0, 0), ofColor(255)));
//    lightParams.add(light2Position.set("light2Position", ofColor(127, 0, 0), ofColor(0, 0), ofColor(255)));

    string guiFile = "settings.xml";
    gui.setup("settings", guiFile);
    gui.add(sceneParams);
    gui.add(materialParams);
    gui.add(renderParams);
    gui.add(lightParams);
    gui.loadFromFile(guiFile);
}

//--------------------------------------------------------------
void ofApp::initShader(){
    shader.load("shaders/reflection");
}

//--------------------------------------------------------------
void ofApp::initCubeMap(){
    cubeMap.loadImages("textures/xpos.jpg",
                       "textures/xneg.jpg",
                       "textures/ypos.jpg",
                       "textures/yneg.jpg",
                       "textures/zpos.jpg",
                       "textures/zneg.jpg");
}

//--------------------------------------------------------------
void ofApp::initModel(){
    model.loadModel("models/skull-01.dae", true);
}

//--------------------------------------------------------------
void ofApp::update(){
    model.update();
    if (autoRotate) model.setRotation(0, ofGetElapsedTimef() * -20, 0.0, 1.0, 0.0);

    light1.setDiffuseColor(ofColor(light1Color));
    light2.setDiffuseColor(ofColor(light2Color));

    light1.setPosition(cos(ofGetElapsedTimef()*.6f) * radius * 2 + center.x,
						   sin(ofGetElapsedTimef()*.8f) * radius * 2 + center.y,
						   -cos(ofGetElapsedTimef()*.8f) * radius * 2 + center.z);
    light2.setPosition( mouseX, mouseY, -300);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(backgroundColor);

    // model
    ofEnableLighting();
    ofEnableDepthTest();
    light1.enable();
    light2.enable();

    cubeMap.bind();
    shader.begin();

    shader.setUniform1i("envMap", 0);
    shader.setUniform1f("reflectivity", reflectivity);
    shader.setUniform1i("combineLightsMode", combineLightsMode);
    shader.setUniform1i("combineEnvironmentMode", combineEnvironmentMode);
    shader.setUniform4f("material.diffuse", (float)diffuse->r/255, (float)diffuse->g/255, (float)diffuse->b/255, (float)diffuse->a/255);
    shader.setUniform4f("material.specular", (float)specular->r/255, (float)specular->g/255, (float)specular->b/255, (float)specular->a/255);
    shader.setUniform4f("material.emission", (float)emissive->r/255, (float)emissive->g/255, (float)emissive->b/255, (float)emissive->a/255);
    shader.setUniform1f("material.shininess", 120.0);

    ofPushMatrix();
    ofTranslate(center.x + gui.getWidth() * 0.5, center.y + 50, -300);
    model.drawFaces();
    ofPopMatrix();

    shader.end();
    cubeMap.unbind();

    light1.disable();
    light2.disable();
    ofDisableDepthTest();
    ofDisableLighting();

    // gui
    if (guiVisible) gui.draw();

    // fps
    ofPushMatrix();
    ofTranslate(ofGetWidth() - 62, 8);
    ofPushStyle();
    ofSetColor(ofColor::black);
    ofRect(0, 0, 54, 20);
    ofSetColor(ofColor::white);
    font.drawString("fps: " + ofToString((int)ofGetFrameRate()), 6, 15);
    ofPopStyle();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    switch (key) {
        case 'g': {
            guiVisible = !guiVisible;
            break;
        }

    }

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
