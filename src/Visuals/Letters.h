#pragma once

#include "ofMain.h"
#include "Scene.h"


class Letters : public Scene
{
public:
    void initialize();
    void update();
    void drawInner();

private:
    ofParameter<int> nrows;
    ofParameter<int> ncols;
    ofParameter<ofVec2f> letterRange;
    ofParameter<int> rate;
    ofParameter<float> density;
    ofParameter<ofColor> color;
    ofParameter<ofVec2f> rateNoise;
    ofParameter<float> rateNoiseTime;
    ofParameter<ofVec2f> letterNoise;
    ofParameter<float> letterNoiseTime;
    ofParameter<bool> noisyLetters;
    ofParameter<bool> chinese;
    
    vector<char> chars;
    vector<int> charsC;
    ofTrueTypeFont font, fontC;
    static const char * alphanum;
};
