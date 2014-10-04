#include "ofMain.h"
#include "ofApp.h"
#include "ofAppDefines.h"

//========================================================================
int main( ){
	ofSetupOpenGL(STAGE_WIDTH, STAGE_HEIGHT, OF_WINDOW);
//	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
