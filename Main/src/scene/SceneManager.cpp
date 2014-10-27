#include "SceneManager.h"
#include "../skull/SkullDelegate.h"


SceneManager::SceneManager() {
    currScene = -1;
}


//--------------------------------------------------------------
void SceneManager::update() {
    
    // set SkullDelegate to the current scene, if the scene doesn't subclass SkullDelegate set it to null
    delegate = dynamic_cast<SkullDelegate *>( get(currScene));
    
    get(currScene)->update();
}

//--------------------------------------------------------------
void SceneManager::add(AbstractScene* scene) {
    
    scenes.push_back(scene);
    scene->setup();
    
}

//--------------------------------------------------------------
void SceneManager::next() {
    
    if (currScene < getNum() - 1) navto(currScene + 1);
    else navto(0);
    
}

//--------------------------------------------------------------
void SceneManager::prev() {
    
    if (currScene > 0) navto(currScene - 1);
    else navto(getNum() - 1);
    
}

//--------------------------------------------------------------
void SceneManager::navto(int index) {
    
    if (currScene == index) return;
    
    if (get(currScene)) {
        nextScene = index;
        ofAddListener(get(currScene)->onHideComplete, this, &SceneManager::onSceneHideComplete);
        get(currScene)->isShowing = false;
        get(currScene)->isHiding = true;
        get(currScene)->hide();
    }
    else {
        currScene = index;
        ofAddListener(get(currScene)->onShowComplete, this, &SceneManager::onSceneShowComplete);
        get(currScene)->isShowing = true;
        get(currScene)->show();
    }
    
}

//--------------------------------------------------------------
void SceneManager::navto(string name) {
    
    navto(get(name)->getIndex());
    
}

//--------------------------------------------------------------
void SceneManager::onSceneShowComplete(bool &b) {
    
    //    cout << "SceneManager::onSceneShowComplete" << endl;
    ofRemoveListener(get(currScene)->onHideComplete, this, &SceneManager::onSceneShowComplete);
    get(currScene)->isShowing = false;
}

//--------------------------------------------------------------
void SceneManager::onSceneHideComplete(bool &b) {
    
    //    cout << "SceneManager::onSceneHideComplete" << endl;
    ofRemoveListener(get(currScene)->onHideComplete, this, &SceneManager::onSceneHideComplete);
    get(currScene)->isHiding = false;
    
    currScene = nextScene;
    ofAddListener(get(currScene)->onShowComplete, this, &SceneManager::onSceneShowComplete);
    get(currScene)->isShowing = true;
    get(currScene)->show();
    
}

//--------------------------------------------------------------
AbstractScene* SceneManager::get(int index) {
    
    for(int i = 0; i < scenes.size(); i++) {
        if (scenes[i]->getIndex() == index) return scenes[i];
    }
    return NULL;
    
}

//--------------------------------------------------------------
AbstractScene* SceneManager::get(string name) {
    
    for(int i = 0; i < scenes.size(); i++) {
        if (scenes[i]->getName() == name) return scenes[i];
    }
    return NULL;
    
}
