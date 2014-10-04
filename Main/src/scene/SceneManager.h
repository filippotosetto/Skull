#pragma once

#include "ofMain.h"
#include "abstract/AbstractScene.h"

class SceneManager {
    public:
        static SceneManager* Instance();

        static void init();
        static void add(AbstractScene* scene);
        static void next();
        static void prev();

        static void navto(int index);
        static void navto(string name);

        static AbstractScene* get(int index);
        static AbstractScene* get(string name);

        static int getNum() { return __instance->scenes.size(); }
        static AbstractScene* getCurrentScene() { return get(__instance->current); }

        static void toggleGUIVisible();

    private:
        static SceneManager* __instance;

        vector<AbstractScene*> scenes;
        int current;
        bool guiVisible;
};

