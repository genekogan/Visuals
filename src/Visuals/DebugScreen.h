#pragma once

#include "ofMain.h"
#include "Scene.h"


class DebugScreen : public Scene
{
public:
    void initialize();
    void update();
    void drawInner();

private:
    enum DebugType { FULL, GRADIENT, CHECKERBOARD, FRAMES };
    
    void drawFull();
    void drawCheckerboard();
    void drawFrames();
    void drawGradient();

    void setType(string s);
    void setupGradient(string gradientType);
    
    void setModeFull(bool & b);
    void setModeGradient(bool & b);
    void setModeCheckerboard(bool & b);
    void setModeFrames(bool & b);
    
    void setGradientModeCircular(bool & b);
    void setGradientModeLinear(bool & b);
    void setGradientModeBar(bool & b);

    void colorChanged(ofColor & c);
    
    ofVboMesh gradientMesh;
    DebugType type = GRADIENT;
    string gradientMode;
    
    ofParameter<ofColor> color1;
    ofParameter<ofColor> color2;
    ofParameter<int> numRects;
    ofParameter<int> speed;
    
    ofxToggle tFull, tGradient, tCheckerboard, tFrames;
    ofxToggle tCircular, tLinear, tBar;

};
