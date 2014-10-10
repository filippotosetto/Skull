#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(0, 0);

    model.loadModel("skull-01.dae", true);
//    model.setPosition(ofGetWidth() * 0.5, ofGetHeight() * 0.5 , 0);

//    material = model.getMaterialForMesh(0);
//    cout << "material 0 color: " << model.getMaterialForMesh(0).getDiffuseColor() << endl;
    material.setDiffuseColor(ofColor::red);

    box.set(50);
    box.setPosition(ofGetWidth()*.5, ofGetHeight()*.5, 0);

    /*
    if(ofGetGLProgrammableRenderer()){
		shader.load("shaders_gl3/noise.vert", "shaders_gl3/noise.frag");
	}else{
		shader.load("shaders/noise.vert", "shaders/noise.frag");
	}
    */

	cubeMapShader.load("shaders/CubeMap");

	cubeMap.loadImages("mountains/xpos.jpg",
                       "mountains/xneg.jpg",
                       "mountains/ypos.jpg",
                       "mountains/yneg.jpg",
                       "mountains/zpos.jpg",
                       "mountains/zneg.jpg");

}

//--------------------------------------------------------------
void ofApp::update(){
    model.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);

    ofEnableDepthTest();
    light.enable();
//    glColor3f(1.0f, 0.2f, 0.2f);
//    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);

    ofPushMatrix();
    ofTranslate(ofGetWidth()*.5, ofGetHeight()*.5, 0);
//    ofRotate(180, 0, 0, 1);
//    ofRotate(ofGetElapsedTimef() * 4, 0, 1.0, 0.0);

    cubeMap.bind();
    cubeMapShader.begin();
    cubeMapShader.setUniform1i("EnvMap", 0);
//    cubeMap.drawSkybox(500);
    model.drawFaces();
    cubeMapShader.end();
    cubeMap.unbind();

    ofPopMatrix();

    box.rotate(spinX, 1.0, 0.0, 0.0);
    box.rotate(spinY, 0, 1.0, 0.0);

    model.setRotation(0, ofGetElapsedTimef() * -10, -1.0, 1.0, 0.0);


//    shader.begin();
    //we want to pass in some varrying values to animate our type / color
//    shader.setUniform1f("timeValX", ofGetElapsedTimef() * 0.1 );
//    shader.setUniform1f("timeValY", -ofGetElapsedTimef() * 0.18 );

    //we also pass in the mouse position
    //we have to transform the coords to what the shader is expecting which is 0,0 in the center and y axis flipped.
//    shader.setUniform2f("mouse", mouseX - ofGetWidth()/2, ofGetHeight()/2-mouseY );

//    box.draw();
//    model.drawFaces();

//    shader.end();

    light.disable();
    ofDisableDepthTest();

    /*
//    ofEnableBlendMode(OF_BLENDMODE_ALPHA);
	ofEnableDepthTest();

//    glShadeModel(GL_SMOOTH); //some model / light stuff
    light.enable();
//    ofEnableSeparateSpecularLight();

//    glEnable(GL_LIGHTING);
//    glEnable(GL_NORMALIZE);
//    glEnable(GL_LIGHT0);

//    glDisable(GL_COLOR_MATERIAL);
    glColor3f(0.2f, 0.2f, 0.2f);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);

    ofPushMatrix();
    ofTranslate(model.getPosition().x, model.getPosition().y, 0);
    ofRotate(-mouseX, 0, 1, 0);
    ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);
    model.drawFaces();
    ofPopMatrix();

    ofDisableDepthTest();
    light.disable();
//    ofDisableLighting();
//    ofDisableSeparateSpecularLight();

//    glDisable(GL_LIGHT0);
//    glDisable(GL_NORMALIZE);
//    glDisable(GL_LIGHTING);
    */

    /*
    // correct result
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHT0);

    ofPushMatrix();
    ofTranslate(model.getPosition().x+150, model.getPosition().y, 0);
    ofRotate(-0, 0, 1, 0);
    ofTranslate(-model.getPosition().x, -model.getPosition().y, 0);
    model.drawFaces();
    ofPopMatrix();

    glDisable(GL_LIGHT0);
    glDisable(GL_NORMALIZE);
    glDisable(GL_LIGHTING);
    */
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
