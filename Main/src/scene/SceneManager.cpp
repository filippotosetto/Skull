#include "SceneManager.h"

SceneManager* SceneManager::__instance = 0;

//--------------------------------------------------------------
SceneManager* SceneManager::Instance() {

	if (__instance == 0) {
		__instance = new SceneManager();
		__instance->currScene = -1;
	}
	return __instance;

}

//--------------------------------------------------------------
void SceneManager::init() {

	Instance();

}

//--------------------------------------------------------------
void SceneManager::update() {

	get(__instance->currScene)->update();

}

//--------------------------------------------------------------
void SceneManager::add(AbstractScene* scene) {

    __instance->scenes.push_back(scene);
    scene->setup();

}

//--------------------------------------------------------------
void SceneManager::next() {

    if (__instance->currScene < __instance->getNum() - 1) navto(__instance->currScene + 1);
    else navto(0);

}

//--------------------------------------------------------------
void SceneManager::prev() {

    if (__instance->currScene > 0) navto(__instance->currScene - 1);
    else navto(__instance->getNum() - 1);

}

//--------------------------------------------------------------
void SceneManager::navto(int index) {

    if (__instance->currScene == index) return;

    if (__instance->get(__instance->currScene)) {
        __instance->nextScene = index;
        ofAddListener(__instance->get(__instance->currScene)->onHideComplete, __instance, &SceneManager::onSceneHideComplete);
        __instance->get(__instance->currScene)->isShowing = false;
        __instance->get(__instance->currScene)->isHiding = true;
        __instance->get(__instance->currScene)->hide();
    }
    else {
        __instance->currScene = index;
        ofAddListener(__instance->get(__instance->currScene)->onShowComplete, __instance, &SceneManager::onSceneShowComplete);
        __instance->get(__instance->currScene)->isShowing = true;
        __instance->get(__instance->currScene)->show();
    }

}

//--------------------------------------------------------------
void SceneManager::navto(string name) {

    navto(__instance->get(name)->getIndex());

}

//--------------------------------------------------------------
void SceneManager::onSceneShowComplete(bool &b) {

    cout << "SceneManager::onSceneShowComplete" << endl;
    ofRemoveListener(__instance->get(__instance->currScene)->onHideComplete, __instance, &SceneManager::onSceneShowComplete);
    __instance->get(__instance->currScene)->isShowing = false;
}

//--------------------------------------------------------------
void SceneManager::onSceneHideComplete(bool &b) {

    cout << "SceneManager::onSceneHideComplete" << endl;
    ofRemoveListener(__instance->get(__instance->currScene)->onHideComplete, __instance, &SceneManager::onSceneHideComplete);
    __instance->get(__instance->currScene)->isHiding = false;

    __instance->currScene = __instance->nextScene;
    ofAddListener(__instance->get(__instance->currScene)->onShowComplete, __instance, &SceneManager::onSceneShowComplete);
    __instance->get(__instance->currScene)->isShowing = true;
    __instance->get(__instance->currScene)->show();

}

//--------------------------------------------------------------
AbstractScene* SceneManager::get(int index) {

    for(int i = 0; i < __instance->scenes.size(); i++) {
        if (__instance->scenes[i]->getIndex() == index) return __instance->scenes[i];
    }
    return NULL;

}

//--------------------------------------------------------------
AbstractScene* SceneManager::get(string name) {

    for(int i = 0; i < __instance->scenes.size(); i++) {
        if (__instance->scenes[i]->getName() == name) return __instance->scenes[i];
    }
    return NULL;

}
