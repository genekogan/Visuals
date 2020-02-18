#pragma once

#include "ofMain.h"
#include "Scene.h"


class GridFly : public Scene
{
public:
    ~GridFly();
    void initialize();
    void update();
    void drawInner();
    
    
private:
    void addRow();
    
    ofMesh mesh;
    ofEasyCam cam;
    
    vector<ofVec3f> *vertices;
    float minY, dy, y, Z;
    ofPoint camPosition = ofPoint(0, 100);
    
    ofParameter<int> nx;
    ofParameter<int> ny;
    ofParameter<ofVec2f> length;
    ofParameter<float> margin;
    ofParameter<ofVec2f> noiseFactor;
    ofParameter<float> speed;
    ofParameter<float> angle;
    ofParameter<ofVec3f> axis;
    ofParameter<ofColor> color;

};


/*
 - random shapes floating around with random data
 - 3d shapes / obj from thingiverse
*/
