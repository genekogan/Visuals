#pragma once

#include "ofMain.h"
#include "Scene.h"


#define FORCE_RESOLUTION 256


class Streak
{
public:
    void setup(float x, float y, int maxAge, float speed,
               int maxThickness, float strokeAlpha,
               int width, int height, ofColor color);
    void update(ofPoint vel);
    void draw();
    bool isActive();

    ofVec2f pos, prev;
    float age, maxAge, speed, speedVar, maxThickness, strokeAlpha;
    ofColor color;
    int width, height;
};


class Rivers : public Scene
{
public:
    void initialize();
    void update();
    void drawInner();

private:
    void setupForceField(string &s);
    void addNewStreak();
    void setupStreak(Streak &streak);
    
    ofParameter<int> numStreaks;
    ofParameter<float> complexity;
    ofParameter<float> baseSpeed;
    ofParameter<float> speedVar;
    ofParameter<int> minAge;
    ofParameter<int> maxAge;
    ofParameter<int> refreshAlpha;
    ofParameter<int> streakAlpha;
    ofParameter<float> maxThickness;
    ofParameter<ofColor> color;
    ofParameter<int> colorVar;
    
    vector<Streak> streaks;
    ofVec2f force[FORCE_RESOLUTION][FORCE_RESOLUTION];
    float noiseSeed;
};
