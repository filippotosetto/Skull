#pragma once

#include "ofMain.h"

#include "ofxXmlSettings.h"
#include "ofxGui.h"
#include "ofxAssimpModelLoader.h"
#include "ofxTweenzor.h"

#include "ui/Drag.h"
#include "skull/Skull.h"
#include "audio/AudioManager.h"
#include "scene/SceneManager.h"


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
		void initDrags();
		void initScenes();
		void initSkull();

		void updatePlane();
		void saveSettings();

		ofPoint lerpPoint(ofPoint start, ofPoint end, float amt);

		// mapping
		ofFbo fbo;
		ofMaterial material;
		ofPlanePrimitive plane;
		vector<Drag> drags;

        // gui
		ofxPanel gui;
		ofxToggle drawScenes;
        ofxToggle drawWireframe;
        ofxToggle drawDistortion;
        ofxToggle drawSkull;
        bool guiVisible = true;

        // 3D
        Skull skull;
};
