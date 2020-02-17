#pragma once

#include "ofMain.h"
#include "Scene.h"


class Amoeba : public Scene
{
public:
    void initialize();
    void update();
    void drawInner();
    
private:
    
    void drawAmoeba();
    
    float time;
    
    ofParameter<int> numVertices;
    ofParameter<ofVec2f> radRange;
    ofParameter<ofVec2f> center;
    ofParameter<float> speed;
    ofParameter<float> noiseFactor;
    ofParameter<float> noiseRegion;
    ofParameter<float> offset;
    ofParameter<ofColor> colorFill;
    ofParameter<ofColor> colorStroke;
    ofParameter<float> lineWidth;
    ofParameter<bool> filled;
    ofParameter<bool> stroked;
    ofParameter<bool> curvedVertices;
    ofParameter<int> cycleStroke;
    ofParameter<float> densityStroke;
    ofParameter<int> cycleFill;
    ofParameter<float> densityFill;

};
