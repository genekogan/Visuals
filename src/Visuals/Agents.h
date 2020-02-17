#pragma once

#include "ofMain.h"
#include "Scene.h"


enum AgentsDrawType { LINES, TRIANGLES };


class Agent
{
public:
    void setup(int x, int y, float baseRad, int width, int height);
    void setSpeed(float speed);
    void setSize(float size);
    void update();
    void wrap();
    void draw();
    void addIntersectingAgent(Agent *other);
    bool isIntersecting(Agent &other);
    vector<Agent *> getIntersecting();

    float rad, baseRad, speed, size;
    int tOffset;
    ofVec2f pos, vel;
    int width, height;
    
protected:
    vector<Agent *> intersecting;
};


class Agents : public Scene
{
public:
    void initialize();
    void update();
    void drawInner();
    
protected:
    void setDrawingMode(string & s);
    void addNewAgent();
    void refresh();
    void drawDebug();

    vector<Agent> agents;
    
    ofParameter<int> numAgents;
    ofParameter<bool> wrapping;
    ofParameter<bool> debug;
    ofParameter<float> speed;
    ofParameter<int> size;
    ofParameter<ofColor> color1;
    ofParameter<ofColor> color2;
    ofParameter<int> fillAlpha;
    ofParameter<int> strokeAlpha;
    ofParameter<float> lineWidth;
    ofParameter<int> cycle;
    ofParameter<float> density;
    ofParameter<bool> drawLines;
    ofParameter<bool> drawTriangles;
  
};
