#include "AudioManager.h"

AudioManager* AudioManager::__instance = 0;

//--------------------------------------------------------------
AudioManager* AudioManager::Instance() {

	if (__instance == 0) {
		__instance = new AudioManager();
		__instance->fft.setup();
	}
	return __instance;

}

//--------------------------------------------------------------
void AudioManager::init() {

	Instance();

}


//--------------------------------------------------------------
void AudioManager::update() {

	__instance->fft.update();

    // cheap beat detection
    float peak = __instance->fft.getAveragePeak();
    __instance->isKick = (peak - __instance->lastAveragePeak > __instance->beatThreshold);
    __instance->lastAveragePeak = peak;


}
