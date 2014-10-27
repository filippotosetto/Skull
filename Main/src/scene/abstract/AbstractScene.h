#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxTweenzor.h"
#include "ofxTimer.h"
#include "ofAppDefines.h"
#include "../../audio/AudioManager.h"

class AbstractScene {
    friend class SceneManager;

    public:
        AbstractScene();
        AbstractScene(int _index, string _name);

        virtual void setup();
        virtual void update();

        virtual void show();
        virtual void show(float millis);
        virtual void hide();
        virtual void hide(float millis);

        virtual void showComplete();
        virtual void showComplete(ofEventArgs &e);
        virtual void hideComplete();
        virtual void hideComplete(ofEventArgs &e);


        int getIndex() { return index; }
        string getName() { return name; }

        ofxPanel gui;

        ofEvent<bool> onShowComplete;
        ofEvent<bool> onHideComplete;

    
        bool isShowing;
        bool isHiding;
    
    protected:
        virtual void initGUI();

        int index;
        string name;


        ofxTimer timer;

};

