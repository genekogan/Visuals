#pragma once

#include "ofMain.h"

#include "Scene.h"
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



class Visual
{
public:
    
    Visual();

    void setup(string sceneType, string presetName, int w, int h);
    void setupFromJson(string jsonPath, int w, int h);
    void update();
    void draw(int x, int y);
    
protected:
    
    Scene *scene;
};

