#pragma once

#include "ofMain.h"
#include "ofxAssimpModelLoader.h"
#include "ofxFFTLive.h"

#include "Circle.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    ofxAssimpModelLoader model;
    
    ofMesh mesh;
    ofLight	light;
    
    ofxFFTLive fftLive;
    int numOfBuckets = 10;
    float * audioData = new float[numOfBuckets];

    
    ofFbo fbo;
    
    vector<Circle> circles;
    
    void bindFBOTexture();
    void unbindFBOTexture();
};
