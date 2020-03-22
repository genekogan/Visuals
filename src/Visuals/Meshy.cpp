#include "Meshy.h"

/*
//--------
void Meshy::initialize() {
    setName("Meshy");
 
    gui.add(realtime.set("realtime", true));
    gui.add(circles.set("circles", true));
    gui.add(filled.set("filled", true));
    gui.add(numCandidates.set("numCandidates", 10, 1, 50));
    gui.add(numPoints.set("numPoints", 100, 10, 1000));
    gui.add(minDist.set("minDist", 130, 0.0, 500.0));
    gui.add(margin.set("margin", 8, 0.0, 60.0));
    gui.add(triNoise.set("triNoise", 0.01, 0.0, 0.01));
    gui.add(colorNoise.set("colorNoise", 0.001, 0.0, 0.01));
    gui.add(color.set("color", ofColor(255, 50)));
    gui.add(varColor.set("varColor", ofColor(20)));
    gui.add(lineWidth.set("lineWidth", 1, 0.0, 5.0));
    //control.addEvent("triangulate", this, &Meshy::triangulate);
 
    string s;
    triangulate(s);
}

//--------
void Meshy::triangulate(string &s) {
    if (circles) {
        circlePacker.clear();
        circlePacker.setBounds(0, 0, width, height);
        circlePacker.setMinDist(minDist);
        circlePacker.addPoints(numPoints);
        triangulator.triangulate(circlePacker.getPoints());
    }
    else {
        pointGenerator.clear();
        pointGenerator.setBounds(0, 0, width, height);
        pointGenerator.setNumberCandidates(numCandidates);
        pointGenerator.addPoints(numPoints);
        triangulator.triangulate(pointGenerator.getPoints());
    }
}

//--------
void Meshy::update() {
    if (realtime) {
        points.clear();
        float x, y;
        for (int i=0; i<numPoints; i++) {
            x = width  * ofNoise(10+0.7*i, triNoise * ofGetFrameNum()+10, 15);
            y = height * ofNoise(20+1.2*i, triNoise * ofGetFrameNum(),    25);
            points.push_back(ofPoint(x, y));
        }
        triangulator.triangulate(points);
    }
    triangles = triangulator.getTriangles();
    vertices = triangulator.getVertices();
}

//--------
void Meshy::drawInner() {
    for (int i=0; i<triangles.size(); i++) {
        
        ITRIANGLE t0 = triangles[i];
        XYZI v1 = vertices[t0.p1];
        XYZI v2 = vertices[t0.p2];
        XYZI v3 = vertices[t0.p3];
        
        float z = abs(v1.x-v2.x) + abs(v3.x-v2.x) + abs(v2.y-v1.y) + abs(v3.y-v2.y);
        if (z > 800) continue;
        
        ofVec3f colorMargin = ofVec3f(ofSignedNoise(colorNoise * ofGetFrameNum(), i, 50),
                                      ofSignedNoise(colorNoise * ofGetFrameNum(), i, 60),
                                      ofSignedNoise(colorNoise * ofGetFrameNum(), i, 70));

        
        ofSetColor(color->r + colorMargin.x * varColor->r,
                   color->g + colorMargin.y * varColor->g,
                   color->b + colorMargin.z * varColor->b,
                   color->a);

        if (filled) {
            ofFill();
            ofSetLineWidth(0);
        }
        else {
            ofNoFill();
            ofSetLineWidth(lineWidth);
        }
        
        ofDrawTriangle(v1.x + margin * ofSignedNoise( 0, i, triNoise * ofGetFrameNum()),
                   v1.y + margin * ofSignedNoise( 5, i, triNoise * ofGetFrameNum()),
                   v2.x + margin * ofSignedNoise(10, i, triNoise * ofGetFrameNum()),
                   v2.y + margin * ofSignedNoise(15, i, triNoise * ofGetFrameNum()),
                   v3.x + margin * ofSignedNoise(20, i, triNoise * ofGetFrameNum()),
                   v3.y + margin * ofSignedNoise(25, i, triNoise * ofGetFrameNum()));
    }
}

*/
