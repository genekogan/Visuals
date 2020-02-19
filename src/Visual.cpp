#include "Visual.h"

//------------------------------------------------------------------
Visual::Visual() {
    
}
    
//------------------------------------------------------------------
void Visual::setup(string sceneType, string presetName, int w, int h) {
    if        (sceneType == "agents") {
        scene = new Agents();
    } else if (sceneType == "amoeba") {
        scene = new Amoeba();
    } else if (sceneType == "bubbles") {
        scene = new Bubbles();
    } else if (sceneType == "cubes") {
        scene = new Cubes();
    } else if (sceneType == "debug") {
        scene = new DebugScreen();
    } else if (sceneType == "gridfly") {
        scene = new GridFly();
    } else if (sceneType == "letters") {
        scene = new Letters();
    } else if (sceneType == "meshy") {
        scene = new Meshy();
    } else if (sceneType == "movie") {
        scene = new MoviePlayer();
    } else if (sceneType == "polar") {
        scene = new Polar();
    } else if (sceneType == "rivers") {
        scene = new Rivers();
    } else if (sceneType == "shader") {
        scene = new Shader();
    } else if (sceneType == "shapespace") {
        scene = new ShapeSpace();
    } else if (sceneType == "subdivide") {
        scene = new Subdivide();
    }
    scene->setup(w, h);
    scene->loadPreset(presetName);
}

//------------------------------------------------------------------
void Visual::setupFromJson(string jsonPath, int w, int h) {
    ofJson json = ofLoadJson(jsonPath);
    string sceneName = json["scene"];
    string presetName = json["preset"];
    setup(sceneName, presetName, w, h);
}

//------------------------------------------------------------------
void Visual::update() {
    scene->update();
}

//------------------------------------------------------------------
void Visual::draw(int x, int y) {
    scene->draw(x, y);
}
