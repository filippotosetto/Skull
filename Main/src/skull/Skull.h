#pragma once

#include "ofMain.h"
#include "ofAppDefines.h"
#include "ofxAssimpModelLoader.h"
#include "ofxCubeMap.h"
#include "ofxXmlSettings.h"

class Skull {
    public:
        Skull();

        void setup();
        void update();
        void draw();

		void loadSettings(string name);

    private:
        void initCamera();
        void initShader();
		void initCubeMap();
		void initModel();
		void initLights();

		ofColor getColorSettings(ofxXmlSettings* settings, string name);
		ofVec3f getPositionSettings(ofxXmlSettings* settings, string name);

        // objects
        ofShader shaderReflection;
		ofShader shaderFresnel;
		ofxAssimpModelLoader modelFlat;
		ofxAssimpModelLoader modelSmooth;
		ofLight light1;
		ofLight light2;
		ofLight light3;

        // parameters
		ofColor emissive;
		ofColor diffuse;
		ofColor specular;
		float shininess;
		float reflectivity;

		int combineLightsMode;
		int combineEnvironmentMode;
		bool reflectionGrayscale;
		bool usePhongShader;
		bool useFlatModel;

		ofColor light1Color;
		ofColor light2Color;
		ofColor light3Color;
		ofVec3f light1Position;
		ofVec3f light2Position;
		ofVec3f light3Orientation;
		float light1Attenuation;
		float light2Attenuation;

		bool useFresnelShader;
        float fresnelRefraction;
        float fresnelBias;
        float fresnelPower;
        float fresnelScale;

        // cube map
		ofxCubeMap cubeMap;
		ofFbo fbo;

        // cam
		ofEasyCam cam;

};
