#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	ofSetLogLevel(OF_LOG_VERBOSE);
//    ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE);
	ofSetupOpenGL(1024, 768, OF_WINDOW);			// <-------- setup the GL context
	ofSetWindowPosition(100, 100);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
