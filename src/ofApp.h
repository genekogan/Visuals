#pragma once

#include "ofMain.h"

#include "Agents.h"
#include "Amoeba.h"
#include "Bubbles.h"
#include "Cubes.h"
#include "DebugScreen.h"
#include "GridFly.h"
#include "Letters.h"
#include "Meshy.h"
#include "MoviePlayer.h"
#include "Polar.h"
#include "Rivers.h"
#include "Shader.h"
#include "ShapeSpace.h"
#include "Subdivide.h"


#include "Visual.h"


class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
protected:
    
    Agents agents;
    Amoeba amoeba;
    Bubbles bubbles;
    Cubes cubes;
    DebugScreen debugscreen;
    GridFly gridfly;
    Letters letters;
    Meshy meshy;
    MoviePlayer movieplayer;
    Polar polar;
    Rivers rivers;    
    Shader shade;
    ShapeSpace shapespace;
    Subdivide subdivide;
    
    Visual visual;
};
