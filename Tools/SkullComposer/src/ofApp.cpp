#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);

    radius = 180.f;
	center.set(ofGetWidth()*.5, ofGetHeight()*.5, 0);

    initGUI();
    initShader();
    initCubeMap();
    initModel();
    initLights();
}

//--------------------------------------------------------------
void ofApp::initGUI(){
    font.loadFont(OF_TTF_SANS, 10, false);

    sceneParams.setName("scene");
	sceneParams.add(backgroundColor.set("backgroundColor", ofColor(0, 0, 0), ofColor(0, 0), ofColor(255)));
	sceneParams.add(drawSkybox.set("drawSkybox", false));

    materialParams.setName("material");
	materialParams.add(emissive.set("emissive", ofColor(127, 0, 0), ofColor(0, 0), ofColor(255)));
	materialParams.add(diffuse.set("diffuse", ofColor(127, 0, 0), ofColor(0, 0), ofColor(255)));
	materialParams.add(specular.set("specular", ofColor(127, 0, 0), ofColor(0, 0), ofColor(255)));
	materialParams.add(shininess.set("shininess", 10, 0, 200));
	materialParams.add(reflectivity.set("reflectivity", 0.5, 0, 1.0));

	renderParams.setName("render");
	renderParams.add(combineLightsMode.set("combineLightsMode", 0, 0, 1));
	renderParams.add(combineEnvironmentMode.set("combineEnvironmentMode", 1, 0, 2));

	lightParams.setName("light");
    lightParams.add(light1Color.set("light1Color", ofColor(127, 0, 0), ofColor(0, 0), ofColor(255)));
    lightParams.add(light1Position.set("light1Position", ofVec3f(-100, 0, 0), ofVec3f(-500), ofVec3f(500)));
    lightParams.add(light2Color.set("light2Color", ofColor(127, 0, 0), ofColor(0, 0), ofColor(255)));
    lightParams.add(light2Position.set("light2Position", ofVec3f(-100, 0, 0), ofVec3f(-500), ofVec3f(500)));
    lightParams.add(drawDebugLights.set("drawDebugLights", true));

    fresnelParams.setName("fresnel");
	fresnelParams.add(useFresnelShader.set("useFresnelShader", false));
    fresnelParams.add(refractionRatio.set("refractionRatio", 1.02, 0, 2.0));
    fresnelParams.add(fresnelBias.set("fresnelBias", 0.1, 0, 1.0));
    fresnelParams.add(fresnelPower.set("fresnelPower", 2.0, 0, 5.0));
    fresnelParams.add(fresnelScale.set("fresnelScale", 1.0, 0, 1.0));

    string guiFile = "settings.xml";
    gui.setup("settings", guiFile);
    gui.add(sceneParams);
    gui.add(materialParams);
    gui.add(lightParams);
    gui.add(renderParams);
    gui.add(fresnelParams);
    gui.loadFromFile(guiFile);

    gui.getGroup("scene").minimize();
    gui.getGroup("material").minimize();
    gui.getGroup("light").minimize();
    gui.getGroup("render").minimize();
    gui.getGroup("fresnel").minimize();
}

//--------------------------------------------------------------
void ofApp::initShader(){
    shaderReflection.load("shaders/reflection");
    shaderFresnel.load("shaders/fresnel");
}

//--------------------------------------------------------------
void ofApp::initCubeMap() {
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
//    model.loadModel("models/skull-01.3ds", true);

    primitive.setRadius(200);
//    primitive.set(200);
//    primitive.set(200, 300);
}

//--------------------------------------------------------------
void ofApp::initLights(){
    sphereDebugLight.setRadius(10);
    ofSetSmoothLighting(true); // set true if model is smooth

//    light2.setSpotlight(50, 45);
}

//--------------------------------------------------------------
void ofApp::update(){
//    model.update();
//    if (autoRotate) model.setRotation(0, ofGetElapsedTimef() * -20, 0.0, 1.0, 0.0);

    light1.setDiffuseColor(ofColor(light1Color));
    light2.setDiffuseColor(ofColor(light2Color));

    /*
    light1.setPosition(cos(ofGetElapsedTimef()*.6f) * radius * 2 + center.x,
						   sin(ofGetElapsedTimef()*.8f) * radius * 2 + center.y,
						   -cos(ofGetElapsedTimef()*.8f) * radius * 2 + center.z);
						   */
//    light2.setOrientation( ofVec3f( 0, cos(ofGetElapsedTimef()) * RAD_TO_DEG, 0) );

    light1.setPosition(light1Position);
    light2.setPosition(light2Position);
    light2Position.set(ofVec3f(mouseX, mouseY, light2Position.get().z));
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(backgroundColor);

    cubeMap.bind();

    // draw skubox
    if (drawSkybox) {
        ofPushMatrix();
        ofTranslate(center.x, center.y);
        ofRotate(180, 0, 0, 1);
        cubeMap.drawSkybox(2000);
        ofPopMatrix();
    }

    ofEnableDepthTest();
    ofEnableLighting();
    light1.enable();
    light2.enable();

    if (!useFresnelShader) {
        shaderReflection.begin();
        shaderReflection.setUniform1i("envMap", 0);
        shaderReflection.setUniform1f("reflectivity", reflectivity);
        shaderReflection.setUniform1i("combineLightsMode", combineLightsMode);
        shaderReflection.setUniform1i("combineEnvironmentMode", combineEnvironmentMode);
        shaderReflection.setUniform4f("material.diffuse", (float)diffuse->r/255, (float)diffuse->g/255, (float)diffuse->b/255, (float)diffuse->a/255);
        shaderReflection.setUniform4f("material.specular", (float)specular->r/255, (float)specular->g/255, (float)specular->b/255, (float)specular->a/255);
        shaderReflection.setUniform4f("material.emission", (float)emissive->r/255, (float)emissive->g/255, (float)emissive->b/255, (float)emissive->a/255);
        shaderReflection.setUniform1f("material.shininess", shininess);
    }

    if (useFresnelShader) {
        shaderFresnel.begin();
        shaderFresnel.setUniform1i("envMap", 0);
        shaderFresnel.setUniform1f("refractionRatio", refractionRatio);
        shaderFresnel.setUniform1f("fresnelBias", fresnelBias);
        shaderFresnel.setUniform1f("fresnelPower", fresnelPower);
        shaderFresnel.setUniform1f("fresnelScale", fresnelScale);
    }

    cam.begin();
    cam.setDistance(1000);
    cam.setVFlip(true);
    model.drawFaces();
    cam.end();

//    ofPushMatrix();
//    ofTranslate(mouseX, mouseY, -100);
//    primitive.drawFaces();
//    ofPopMatrix();

    if (!useFresnelShader) shaderReflection.end();
    if (useFresnelShader) shaderFresnel.end();

    cubeMap.unbind();

    light1.disable();
    light2.disable();
    ofDisableLighting();
    ofDisableDepthTest();

    // debug lights
    if (drawDebugLights) {
        ofPushStyle();
        ofSetColor(light1.getDiffuseColor());
        sphereDebugLight.setPosition(light1.getPosition());
        sphereDebugLight.draw();
        ofSetColor(light2.getDiffuseColor());
        sphereDebugLight.setPosition(light2.getPosition());
        sphereDebugLight.draw();
        ofPopStyle();
    }

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
