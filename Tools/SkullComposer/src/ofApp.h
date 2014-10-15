#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"
#include "ofxCubeMap.h"

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

		void initGUI();
		void initShader();
		void initCubeMap();
		void initModel();
		void initLights();

		float radius;
        ofVec3f center;
        bool guiVisible = true;

		ofTrueTypeFont font;

		ofxPanel gui;
		ofParameterGroup sceneParams;
		ofParameterGroup materialParams;
		ofParameterGroup renderParams;
		ofParameterGroup lightParams;
		ofParameterGroup fresnelParams;

		ofParameter<ofColor> backgroundColor;
		ofParameter<ofColor> emissive;
		ofParameter<ofColor> diffuse;
		ofParameter<ofColor> specular;
		ofParameter<float> shininess;
		ofParameter<float> reflectivity;
		ofParameter<int> combineLightsMode;
		ofParameter<int> combineEnvironmentMode;
		ofParameter<ofColor> light1Color;
		ofParameter<ofColor> light2Color;
		ofParameter<bool> autoRotate;
		ofParameter<bool> drawDebugLights;
        ofParameter<float> mRefractionRatio;
        ofParameter<float> mFresnelBias;
        ofParameter<float> mFresnelPower;
        ofParameter<float> mFresnelScale;

		ofShader shader;
		ofxAssimpModelLoader model;
		ofLight light1;
		ofLight light2;
		ofSpherePrimitive sphereDebugLight;
		ofSpherePrimitive primitive;

		ofxCubeMap cubeMap;

};
