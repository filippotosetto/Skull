#pragma once

#include "ofMain.h"
#include "abstract/AbstractScene.h"
#include "../skull/SkullDelegate.h"

class SceneManager {
public:
    
    SceneManager();
    
    //    void init();
    void update();
    void add(AbstractScene* scene);
    void next();
    void prev();
    
    void navto(int index);
    void navto(string name);
    
    AbstractScene* get(int index);
    AbstractScene* get(string name);
    
    int getNum() { return scenes.size(); }
    AbstractScene* getCurrentScene() { return get(currScene); }
    
    void toggleGUIVisible();
    
    SkullDelegate *delegate;
    
private:
    
    vector<AbstractScene*> scenes;
    int currScene;
    int nextScene;
    bool guiVisible;
    
    void onSceneShowComplete(bool &b);
    void onSceneHideComplete(bool &b);
};


