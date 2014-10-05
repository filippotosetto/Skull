#pragma once

#include "ofMain.h"

#include "ofxXmlSettings.h"
#include "ofxGui.h"

#include "ui/Drag.h"
#include "audio/AudioManager.h"
#include "scene/SceneManager.h"
#include "scene/abstract/AbstractScene.h"
#include "scene/example/ExampleScene.h"


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

		void updateMesh();
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
        bool guiVisible = true;

};
