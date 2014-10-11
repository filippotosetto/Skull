#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofBackground(0, 0);

    model.loadModel("skull-01.dae", true);

    radius		= 180.f;
	center.set(ofGetWidth()*.5, ofGetHeight()*.5, 0);

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

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    pointLight.setDiffuseColor( ofColor(0.f, 255.f, 0.f));
//    pointLight.setSpecularColor( ofColor(0.f, 255.f, 0.f));
//	pointLight.setPosition(0.0, 0.0, 0.0);
//	pointLight.setPosition(-200.0, 200.0, 000.0);
//	pointLight.setSpotlight(45.f, 100.f);

	spotLight.setDiffuseColor( ofColor(255.f, 0.f, 0.f));
//	pointLight.setSpecularColor( ofColor(255.f, 0.f, 0.f));
//	spotLight.setPosition(200.0, -500.0, 000.0);
//    spotLight.setSpotlight(45.f, 1.f);
//    spotLight.setSpotConcentration( 45 );

}

//--------------------------------------------------------------
void ofApp::update(){
    model.update();

    pointLight.setPosition(cos(ofGetElapsedTimef()*.6f) * radius * 2 + center.x,
						   sin(ofGetElapsedTimef()*.8f) * radius * 2 + center.y,
						   -cos(ofGetElapsedTimef()*.8f) * radius * 2 + center.z);
    spotLight.setPosition( mouseX, mouseY, 400);
}

//--------------------------------------------------------------
void ofApp::draw(){

    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);

//    ofEnableDepthTest();
//    light.enable();
//    glColor4f(1.0, 0.2, 0.2, 1.0);
//    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT);


    /*
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);

    // Light model parameters:
    // -------------------------------------------

    GLfloat lmKa[] = {0.0, 0.0, 0.0, 0.0 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmKa);

    glLightModelf(GL_LIGHT_MODEL_LOCAL_VIEWER, 1.0);
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

    // -------------------------------------------
    // Spotlight Attenuation

    GLfloat spot_direction[] = {1.0, -1.0, -1.0 };
    GLint spot_exponent = 30;
    GLint spot_cutoff = 180;

    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
    glLighti(GL_LIGHT0, GL_SPOT_EXPONENT, spot_exponent);
    glLighti(GL_LIGHT0, GL_SPOT_CUTOFF, spot_cutoff);

    GLfloat Kc = 1.0;
    GLfloat Kl = 0.0;
    GLfloat Kq = 0.0;

    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION,Kc);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Kl);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Kq);


    // -------------------------------------------
    // Lighting parameters:

    GLfloat light_pos[] = {0.0f, 5.0f, 5.0f, 1.0f};
    GLfloat light_Ka[]  = {1.0f, 0.5f, 0.5f, 1.0f};
    GLfloat light_Kd[]  = {1.0f, 0.1f, 0.1f, 1.0f};
    GLfloat light_Ks[]  = {0.0f, 1.0f, 0.0f, 1.0f};

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_Ka);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_Kd);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_Ks);

    // -------------------------------------------
    // Material parameters:

    GLfloat material_Ka[] = {0.5f, 0.0f, 0.0f, 1.0f};
    GLfloat material_Kd[] = {0.4f, 0.4f, 0.5f, 1.0f};
    GLfloat material_Ks[] = {0.8f, 0.8f, 0.0f, 1.0f};
    GLfloat material_Ke[] = {0.1f, 0.0f, 1.0f, 1.0f};
    GLfloat material_Se = 2.0f;

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, material_Ka);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, material_Kd);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_Ks);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_Ke);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, material_Se);
    */

    ofEnableLighting();
//    pointLight.enable();
    spotLight.enable();

    ofPushMatrix();
    ofTranslate(ofGetWidth()*.5, ofGetHeight()*.5, 0);
//    ofRotate(180, 0, 0, 1);
//    ofRotate(ofGetElapsedTimef() * 4, 0, 1.0, 0.0);

    cubeMap.bind();
    cubeMapShader.begin();
    cubeMapShader.setUniform1i("envMap", 0);
    cubeMapShader.setUniform1f("reflectivity", 0.8);
    cubeMapShader.setUniform1i("combine", 1);
    cubeMapShader.setUniform4f("material.ambient", 0.0f, 0.0f, 0.0f, 1.0f);
    cubeMapShader.setUniform4f("material.diffuse", 1.0f, 1.0f, 1.0f, 1.0f);
    cubeMapShader.setUniform4f("material.specular", 0.8f, 0.8f, 0.8f, 1.0f);
    cubeMapShader.setUniform4f("material.emission", 0.0f, 0.0f, 0.0f, 1.0f);
    cubeMapShader.setUniform1f("material.shininess", 2.0);
//    cubeMap.drawSkybox(500);
    model.drawFaces();
    cubeMapShader.end();
    cubeMap.unbind();

    ofPopMatrix();

    box.rotate(spinX, 1.0, 0.0, 0.0);
    box.rotate(spinY, 0, 1.0, 0.0);

//    glDisable(GL_NORMALIZE);
//    glDisable(GL_LIGHT0);
//    glDisable(GL_LIGHTING);

    spotLight.disable();
    pointLight.disable();
    ofDisableLighting();

//    model.setRotation(0, ofGetElapsedTimef() * -20, 0.0, 1.0, 0.0);


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

//    light.disable();
//    ofDisableDepthTest();

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
