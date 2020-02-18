#pragma once

#include "ofMain.h"
#include "Scene.h"


class ShapeSpace : public Scene
{
public:
    ~ShapeSpace();
    void initialize();
    void update();
    void drawInner();
    
private:
    ofEasyCam cam;
    ofLight light;
    
    ofParameter<int> numElements;
    ofParameter<ofVec3f> size;
    ofParameter<ofVec3f> noiseSpeed;
    ofParameter<ofColor> color;
    ofParameter<ofColor> colorVar;
};



