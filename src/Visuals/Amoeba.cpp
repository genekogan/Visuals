#include "Amoeba.h"

//--------
void Amoeba::initialize() {
    setName("Amoeba");
    
    gui.add(center.set("center", ofVec2f(0.5, 0.5), ofVec2f(0, 0), ofVec2f(1, 1)));
    gui.add(numVertices.set("numVertices", 200, 3, 1000));
    gui.add(radRange.set("radRange", ofVec2f(0, width/3), ofVec2f(-width, -width), ofVec2f(width, width)));
    gui.add(speed.set("speed", 0.01, 0.0, 0.1));
    gui.add(noiseFactor.set("noiseFactor", 0.07, 0.0, 0.1));
    gui.add(noiseRegion.set("noiseRegion", 0.0, -5.0, 5.0));
    gui.add(offset.set("offset", 0.0, -4.0, 4.0));
    gui.add(colorFill.set("colorFill", ofColor(255, 100)));
    gui.add(colorStroke.set("colorStroke", ofColor(255, 100)));
    gui.add(lineWidth.set("lineWidth", 1.0, 0.0, 16.0));
    gui.add(filled.set("filled", false));
    gui.add(cycleFill.set("filledCycle", 50, 4, 200 ));
    gui.add(densityFill.set("filledDensity", 1.0, 0.0, 1.0));
    gui.add(stroked.set("stroked", true));
    gui.add(cycleStroke.set("strokedCycle", 50, 4, 200));
    gui.add(densityStroke.set("strokedDensity", 1.0, 0.0, 1.0));
    gui.add(curvedVertices.set("curvedVertices", false));
}

//--------
void Amoeba::update() {
    time += speed;
}

//--------
void Amoeba::drawInner() {
    if (filled) {
        float t = (float) (ofGetFrameNum() % cycleFill) / cycleFill;
        if (t < densityFill) {
            ofFill();
            ofSetColor(colorFill);
            ofSetLineWidth(0);
            drawAmoeba();
        }
    }
    if (stroked) {
        float t = (float) (ofGetFrameNum() % cycleStroke) / cycleStroke;
        if (t < densityStroke) {
            ofNoFill();
            ofSetColor(colorStroke);
            ofSetLineWidth(lineWidth);
            drawAmoeba();
        }
    }
}

//--------
void Amoeba::drawAmoeba() {
    ofBeginShape();
    float ang, rad0, rad, x, y;
    for (int i=0; i<numVertices; i++) {
        ang = ofMap(i, 0, numVertices, 0, TWO_PI);
        rad0 = ofNoise(offset + noiseFactor * i, noiseRegion, time);
        rad = ofMap(rad0, 0, 1, radRange->x, radRange->y);
        x = width * center->x + rad * cos(ang);
        y = height * center->y + rad * sin(ang);
        if (curvedVertices) {
            ofCurveVertex(x, y);
        }
        else {
            ofVertex(x, y);
        }
    }
    ofEndShape(true);
}
