#include "SceneManager.h"

SceneManager* SceneManager::__instance = 0;

//--------------------------------------------------------------
SceneManager* SceneManager::Instance() {

	if (__instance == 0) {
		__instance = new SceneManager();
		__instance->current = -1;
	}
	return __instance;

}

//--------------------------------------------------------------
void SceneManager::init() {

	Instance();

}

//--------------------------------------------------------------
void SceneManager::add(AbstractScene* scene) {

    __instance->scenes.push_back(scene);
    scene->setup();

}

//--------------------------------------------------------------
void SceneManager::next() {

    if (__instance->current < __instance->getNum() - 1) navto(__instance->current + 1);
    else navto(0);

}

//--------------------------------------------------------------
void SceneManager::prev() {

    if (__instance->current > 0) navto(__instance->current - 1);
    else navto(__instance->getNum() - 1);

}

//--------------------------------------------------------------
void SceneManager::navto(int index) {

    if (__instance->current == index) return;

    if (__instance->get(__instance->current)) __instance->get(__instance->current)->hide();
    __instance->get(index)->show();

    __instance->current = index;

}

//--------------------------------------------------------------
void SceneManager::navto(string name) {

    navto(__instance->get(name)->getIndex());

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
