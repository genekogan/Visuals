#include "ShapeSpace.h"


//--------
void ShapeSpace::initialize() {
    setName("ShapeSpace");
 
    gui.add(numElements.set("numElements", 16, 1, 500));
    gui.add(size.set("size", ofVec3f(50, 50, 50), ofVec3f(0, 0, 0), ofVec3f(250, 250, 250)));
    gui.add(noiseSpeed.set("noiseSpeed", ofVec3f(0.001, 0.001, 0.001), ofVec3f(0, 0, 0), ofVec3f(0.01, 0.01, 0.1)));
    gui.add(color.set("color", ofColor(255, 80)));
    gui.add(colorVar.set("colorVar", ofColor(80)));
    
	light.setPosition(1000, 1000, 2000);
}

//--------
void ShapeSpace::update() {
    
}

//--------
void ShapeSpace::drawInner() {
    cam.begin();
    
    for (int i=0; i<numElements; i++) {
        ofSetColor(color->r + ofSignedNoise(0.001*ofGetFrameNum()+10, 10+5*i, 45) * colorVar->r,
                   color->g + ofSignedNoise(0.001*ofGetFrameNum()+30, 23+7*i, 55) * colorVar->g,
                   color->b + ofSignedNoise(0.001*ofGetFrameNum()+20, 17-3*i, 65) * colorVar->b,
                   color->a);
        
        
        ofDrawBox(width  * ofSignedNoise(noiseSpeed->x * ofGetFrameNum()+20, 11*i+9, 35),
                  height * ofSignedNoise(noiseSpeed->y * ofGetFrameNum()+30, 17*i+13, 15),
                  -1000.0f *     ofNoise(noiseSpeed->z * ofGetFrameNum()+10, 23*i-17, 25),
                  size->x, size->y, size->z);
    }
    
    cam.end();
}

//-------
ShapeSpace::~ShapeSpace(){
    cam.disableMouseMiddleButton();
    cam.disableMouseInput();
}
