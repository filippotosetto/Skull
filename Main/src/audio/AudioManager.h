#pragma once

#include "ofMain.h"
#include "ofxFFTLive.h"

class AudioManager {
    public:
        static AudioManager* Instance();

        static void init();
        static void update();

        static ofxFFTLive* getFFT() { return &(__instance->fft); }

        static void setBeatThreshold(float threshold) { __instance->beatThreshold = threshold; }
        static bool getKick() { return __instance->isKick; }

    private:
        static AudioManager* __instance;

        ofxFFTLive fft;

        bool isKick;
        float beatThreshold = 0.1f;
        float lastAveragePeak = 0.f;
};
