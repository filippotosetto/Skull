#include "Skull.h"

//--------------------------------------------------------------
Skull::Skull() {

}

//--------------------------------------------------------------
void Skull::setup() {

    initCamera();
    initShader();
    initCubeMap();
    initModel();
    initLights();
    loadSettings("example");

}

// -------------------------------------------------------------
void Skull::initCamera() {

    cam.setVFlip(true);
    cam.setDistance(1000);

}

//--------------------------------------------------------------
void Skull::initShader() {

    shaderReflection.load("shaders/reflection_gouraud");
    shaderFresnel.load("shaders/fresnel");

}

//--------------------------------------------------------------
void Skull::initCubeMap() {

    /*
    cubeMap.loadImages("textures/xpos.jpg",
                       "textures/xneg.jpg",
                       "textures/ypos.jpg",
                       "textures/yneg.jpg",
                       "textures/zpos.jpg",
                       "textures/zneg.jpg");
                       */

    cubeMap.initEmptyTextures(512);

    // fbo
    fbo.allocate(1024, 1024, GL_RGBA);

}

//--------------------------------------------------------------
void Skull::initModel() {

    modelFlat.loadModel("models/skull-01.dae");
    modelSmooth.loadModel("models/skull-01.3ds");

}

//--------------------------------------------------------------
void Skull::initLights() {

//    ofSetSmoothLighting(true);
    light3.setDirectional();

}

//--------------------------------------------------------------
void Skull::loadSettings(string name) {

    ofxXmlSettings settings;
    settings.loadFile("scenes/" + name + "/settings.xml");

    emissive                = getColorSettings(&settings, "group:settings:material:emissive");
    diffuse                 = getColorSettings(&settings, "group:settings:material:diffuse");
    specular                = getColorSettings(&settings, "group:settings:material:specular");
    shininess               = settings.getValue("group:settings:material:shininess", 10);
    reflectivity            = settings.getValue("group:settings:material:reflectivity", 0.5);

    combineLightsMode       = settings.getValue("group:settings:render:combineLightsMode", 0);
    combineEnvironmentMode  = settings.getValue("group:settings:render:combineEnvironmentMode", 1);
    reflectionGrayscale     = settings.getValue("group:settings:render:reflectionGrayscale", 0);
    useFlatModel            = settings.getValue("group:settings:render:useFlatModel", 1);

    light1.setDiffuseColor(getColorSettings(&settings, "group:settings:light:light1Color"));
    light2.setDiffuseColor(getColorSettings(&settings, "group:settings:light:light2Color"));
    light3.setDiffuseColor(getColorSettings(&settings, "group:settings:light:light3Color"));

    light1.setPosition(getPositionSettings(&settings, "group:settings:light:light1Position"));
    light2.setPosition(getPositionSettings(&settings, "group:settings:light:light2Position"));
    light3.setOrientation(getPositionSettings(&settings, "group:settings:light:light3Orientation"));

    light1.setAttenuation(settings.getValue("group:settings:light:light1Attenuation", 1));
    light2.setAttenuation(settings.getValue("group:settings:light:light2Attenuation", 1));

    useFresnelShader        = settings.getValue("group:settings:fresnel:useFresnelShader", 0);
    fresnelRefraction       = settings.getValue("group:settings:fresnel:fresnelRefraction", 1.02);
    fresnelBias             = settings.getValue("group:settings:fresnel:fresnelBias", 0.1);
    fresnelPower            = settings.getValue("group:settings:fresnel:fresnelPower", 2.0);
    fresnelScale            = settings.getValue("group:settings:fresnel:fresnelScale", 1.0);

}

//--------------------------------------------------------------
ofColor Skull::getColorSettings(ofxXmlSettings* settings, string name) {

    string strColor = settings->getValue(name, "");
    vector<string> strings = ofSplitString(strColor, ", ");
    return ofColor(ofToInt(strings[0]), ofToInt(strings[1]), ofToInt(strings[2]), ofToInt(strings[3]));

}

//--------------------------------------------------------------
ofVec3f Skull::getPositionSettings(ofxXmlSettings* settings, string name) {

    string strPos = settings->getValue(name, "");
    vector<string> strings = ofSplitString(strPos, ", ");
    return ofVec3f(ofToFloat(strings[0]), ofToFloat(strings[1]), ofToFloat(strings[2]));

}

//--------------------------------------------------------------
void Skull::update() {

}

//--------------------------------------------------------------
void Skull::draw() {

    cubeMap.bind();

    /*
    // draw skubox
    ofPushMatrix();
    ofTranslate(center.x, center.y);
    ofRotate(180, 0, 0, 1);
    cubeMap.drawSkybox(2000);
    ofPopMatrix();
    */

    ofEnableDepthTest();
    ofEnableLighting();
    light1.enable();
    light2.enable();
    light3.enable();

    if (!useFresnelShader) {
        shaderReflection.begin();
        shaderReflection.setUniform1i("envMap", 0);
        shaderReflection.setUniform1f("reflectivity", reflectivity);
        shaderReflection.setUniform1i("combineLightsMode", combineLightsMode);
        shaderReflection.setUniform1i("combineEnvironmentMode", combineEnvironmentMode);
        shaderReflection.setUniform1f("reflectionGrayscale", reflectionGrayscale);
        shaderReflection.setUniform4f("material.diffuse", (float)diffuse.r/255, (float)diffuse.g/255, (float)diffuse.b/255, (float)diffuse.a/255);
        shaderReflection.setUniform4f("material.specular", (float)specular.r/255, (float)specular.g/255, (float)specular.b/255, (float)specular.a/255);
        shaderReflection.setUniform4f("material.emission", (float)emissive.r/255, (float)emissive.g/255, (float)emissive.b/255, (float)emissive.a/255);
        shaderReflection.setUniform1f("material.shininess", shininess);
    }

    if (useFresnelShader) {
        shaderFresnel.begin();
        shaderFresnel.setUniform1i("envMap", 0);
        shaderFresnel.setUniform1f("fresnelRefraction", fresnelRefraction);
        shaderFresnel.setUniform1f("fresnelBias", fresnelBias);
        shaderFresnel.setUniform1f("fresnelPower", fresnelPower);
        shaderFresnel.setUniform1f("fresnelScale", fresnelScale);
    }

    // draw model
    cam.begin();
    if (useFlatModel) modelFlat.drawFaces();
    else modelSmooth.drawFaces();
    cam.end();

    if (!useFresnelShader) shaderReflection.end();
    if (useFresnelShader) shaderFresnel.end();

    cubeMap.unbind();

    light1.disable();
    light2.disable();
    light3.disable();
    ofDisableLighting();
    ofDisableDepthTest();

}
