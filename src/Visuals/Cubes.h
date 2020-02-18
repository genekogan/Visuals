#pragma once

#include "ofMain.h"
#include "Scene.h"
#include "TimeFunction.h"


class Cube
{
public:
    void setup(ofVec3f mainPosition, ofVec3f marginPosition, ofVec3f targetSize, ofVec3f marginSize, ofVec3f ang, ofVec3f dAng, ofColor color, ofParameter<ofVec3f> & pan);
    void draw();
    
private:
    ofVec3f mainPosition, marginPosition, wPosition;
    ofVec3f mainSize, targetSize, marginSize, wSize;
    ofVec3f ang, dAng;
    ofVec3f offsetP, offsetS;
    ofColor color;
    ofParameter<ofVec3f> pan;
};


class Cubes : public Scene
{
public:
    void initialize();
    void update();
    void drawInner();
        
    void preset1();
    void preset2();
    void preset3();
    void preset4();
    void preset5();
    void preset6();
    void preset7();

private:
    void resetTimeFunctions();
    void addNewBox();

    int MAXBOXES = 200;
    vector<Cube> cubes;
    ofVec3f panPosition;
    
    TimeFunction<ofVec3f> mainPosition, marginPosition;
    TimeFunction<ofVec3f> targetSize, marginSize;
    TimeFunction<ofVec3f> ang, dAng;
    
    ofParameter<ofVec2f> translation;
    ofParameter<ofVec3f> pan;
    ofParameter<int> newBoxRate;
    ofParameter<ofColor> color;
    ofParameter<int> colorVar;
    
    ofxButton bPreset1;
    ofxButton bPreset2;
    ofxButton bPreset3;
    ofxButton bPreset4;
    ofxButton bPreset5;
    ofxButton bPreset6;
    ofxButton bPreset7;
};

