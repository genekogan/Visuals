#include "DebugScreen.h"


//--------
void DebugScreen::initialize() {
    setName("DebugScreen");

    vector<string> debugModes;
    debugModes.push_back("Full");
    debugModes.push_back("Gradient");
    debugModes.push_back("Checkerboard");
    debugModes.push_back("Frames");

    vector<string> gradientModes;
    gradientModes.push_back("Circular");
    gradientModes.push_back("Linear");
    gradientModes.push_back("Bar");
    
    
    tFull.addListener(this, &DebugScreen::setModeFull);
    tGradient.addListener(this, &DebugScreen::setModeGradient);
    tCheckerboard.addListener(this, &DebugScreen::setModeCheckerboard);
    tFrames.addListener(this, &DebugScreen::setModeFrames);

    tCircular.addListener(this, &DebugScreen::setGradientModeCircular);
    tLinear.addListener(this, &DebugScreen::setGradientModeLinear);
    tBar.addListener(this, &DebugScreen::setGradientModeBar);

    color1.addListener(this, &DebugScreen::colorChanged);
    color2.addListener(this, &DebugScreen::colorChanged);
    
    gui.add(color1.set("color1", ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 255)));
    gui.add(color2.set("color2", ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 255)));
    gui.add(numRects.set("numRects", 8, 1, 100));
    gui.add(speed.set("speed", 60, 0, 100));
    
    gui.add(tFull.setup("mode: full", true));
    gui.add(tGradient.setup("mode: gradient", false));
    gui.add(tCheckerboard.setup("mode: checkerboard", false));
    gui.add(tFrames.setup("mode: frames", false));
    
    gui.add(tCircular.setup("gradient: circular", false));
    gui.add(tLinear.setup("gradient: linear", true));
    gui.add(tBar.setup("gradient: bar", false));
    
    //control.addEvent("refresh", this, &DebugScreen::refresh);
    
    setupGradient("Linear");
    setType("Full");
}

//--------
void DebugScreen::colorChanged(ofColor & c) {
    if (type == GRADIENT) {
        setupGradient(gradientMode);
    }
}

//--------
void DebugScreen::setGradientModeCircular(bool & b) {
    tCircular = b;
    if (b) {
        tLinear = false;
        tBar = false;
        setupGradient("Circular");
    }
}

//--------
void DebugScreen::setGradientModeLinear(bool & b) {
    tLinear = b;
    if (b) {
        tCircular = false;
        tBar = false;
        setupGradient("Linear");
    }
}

//--------
void DebugScreen::setGradientModeBar(bool & b) {
    tBar = b;
    if (b) {
        tCircular = false;
        tLinear = false;
        setupGradient("Bar");
    }
}


//--------
void DebugScreen::setModeFull(bool & b) {
    tFull = b;
    if (b) {
        tGradient = false;
        tCheckerboard = false;
        tFrames = false;
        setType("Full");
    }
}

//--------
void DebugScreen::setModeGradient(bool & b) {
    tGradient = b;
    if (b) {
        tFull = false;
        tCheckerboard = false;
        tFrames = false;
        setType("Gradient");
    }
}

//--------
void DebugScreen::setModeCheckerboard(bool & b) {
    tCheckerboard = b;
    if (b) {
        tFull = false;
        tGradient = false;
        tFrames = false;
        setType("Checkerboard");
    }
}

//--------
void DebugScreen::setModeFrames(bool & b) {
    tFrames = b;
    if (b) {
        tFull = false;
        tGradient = false;
        tCheckerboard = false;
        setType("Framees");
    }
}

    
//--------
void DebugScreen::setType(string s) {
    if      (s == "Full")           type = FULL;
    else if (s == "Gradient")       type = GRADIENT;
    else if (s == "Checkerboard")   type = CHECKERBOARD;
    else if (s == "Frames")         type = FRAMES;
}

//--------
void DebugScreen::update() {
    
}

//--------
void DebugScreen::drawInner() {
    if (type == FULL) {
        drawFull();
    } else if (type == CHECKERBOARD) {
        drawCheckerboard();
    } else if (type == FRAMES) {
        drawFrames();
    } else if (type == GRADIENT) {
        drawGradient();
    }
}

//--------
void DebugScreen::drawFull() {
    ofSetColor(color1);
    ofFill();
    ofDrawRectangle(0, 0, width, height);
}

//--------
void DebugScreen::drawCheckerboard() {
    ofSetColor(color2);
    ofDrawRectangle(0, 0, width, height);
    
    float x, y, w, h;
    w = width / numRects;
    h = height / numRects;
    
    ofSetColor(color1);
    for (int i=0; i<numRects; i++){
        for (int j=0; j<numRects; j++) {
            if ((i+j)%2==0) continue;
            x = ofMap(i, 0, numRects, 0, width);
            y = ofMap(j, 0, numRects, 0, height);
            ofDrawRectangle(x, y, w, h);
        }
    }
}

//--------
void DebugScreen::drawFrames() {
    ofSetColor(color1);
    ofNoFill();
    ofSetLineWidth((float) width/ numRects);
    
    float x, y, w, h, di;
    if (speed == 0) di = 0;
    else    di = (ofGetFrameNum() % speed) / (float)speed;
    for (int i=0; i<numRects; i++) {
        x = ofMap(i + di, 0, numRects, 0, width/2.0);
        y = ofMap(i + di, 0, numRects, 0, height/2.0);
        w = ofMap(i + di, 0, numRects, width, 0);
        h = ofMap(i + di, 0, numRects, height, 0);
        ofDrawRectangle(x, y, w, h);
    }

    ofSetLineWidth(12);
    ofSetColor(color2);
    ofDrawRectangle(6, 6, width-12, height-12);
}

//--------
void DebugScreen::drawGradient() {
    GLboolean depthMaskEnabled;
    glGetBooleanv(GL_DEPTH_WRITEMASK, &depthMaskEnabled);
    glDepthMask(GL_FALSE);
    gradientMesh.draw();
    if (depthMaskEnabled){
        glDepthMask(GL_TRUE);
    }
}

//--------
void DebugScreen::setupGradient(string gradientMode) {
    this->gradientMode = ofToString(gradientMode);

    gradientMesh.clear();
    gradientMesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    gradientMesh.setUsage(GL_STREAM_DRAW);
    
    if (gradientMode == "Circular") {
        glm::vec3 center;
        center.x = width / 2;
        center.y = height / 2;
        gradientMesh.addVertex(center);
        gradientMesh.addColor(ofColor(color1));
        int n = 64;
        float angleBisector = TWO_PI / (n * 2);
        float smallRadius = ofDist(0, 0, width / 2, height / 2);
        float bigRadius = smallRadius / cos(angleBisector);
        for(int i = 0; i <= n; i++) {
            float theta = i * TWO_PI / n;
            glm::vec3 v;
            v.x = center.x + sin(theta);
            v.y = cos(theta) * bigRadius;
            gradientMesh.addVertex(v);
            gradientMesh.addColor(ofColor(color2));
        }
    }
    else if (gradientMode == "Linear") {
        glm::vec3 v1, v2, v3, v4;
        v1.x = 0;
        v1.y = 0;
        v2.x = width;
        v2.y = 0;
        v3.x = width;
        v3.y = height;
        v4.x = 0;
        v4.y = height;

        gradientMesh.addVertex(v1);
        gradientMesh.addVertex(v2);
        gradientMesh.addVertex(v3);
        gradientMesh.addVertex(v4);
        gradientMesh.addColor(ofColor(color1));
        gradientMesh.addColor(ofColor(color1));
        gradientMesh.addColor(ofColor(color2));
        gradientMesh.addColor(ofColor(color2));
    }
    else if (gradientMode == "Bar") {
        glm::vec3 v1, v2, v3, v4, v5, v6, v7, v8;
        
        v1.x = width / 2;
        v1.y = height / 2;
        v2.x = 0;
        v2.y = height / 2;
        v3.x = 0;
        v3.y = 0;
        v4.x = width;
        v4.y = 0;
        v5.x = width;
        v5.y = height / 2;
        v6.x = width;
        v6.y = height;
        v7.x = 0;
        v7.y = height;
        v8.x = 0;
        v8.y = height / 2;

        gradientMesh.addVertex(v1);
        gradientMesh.addVertex(v2);
        gradientMesh.addVertex(v3);
        gradientMesh.addVertex(v4);
        gradientMesh.addVertex(v5);
        gradientMesh.addVertex(v6);
        gradientMesh.addVertex(v7);
        gradientMesh.addVertex(v8);
        
        gradientMesh.addColor(ofColor(color1));
        gradientMesh.addColor(ofColor(color1));
        gradientMesh.addColor(ofColor(color2));
        gradientMesh.addColor(ofColor(color2));
        gradientMesh.addColor(ofColor(color1));
        gradientMesh.addColor(ofColor(color2));
        gradientMesh.addColor(ofColor(color2));
        gradientMesh.addColor(ofColor(color1));
    }
    
}

