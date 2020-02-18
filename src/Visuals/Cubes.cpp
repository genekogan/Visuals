#include "Cubes.h"


//---------
void Cube::setup(ofVec3f mainPosition, ofVec3f marginPosition, ofVec3f targetSize, ofVec3f marginSize, ofVec3f ang, ofVec3f dAng, ofColor color, ofParameter<ofVec3f> & pan) {
    this->mainPosition = mainPosition;
    this->marginPosition = marginPosition;
    wPosition = ofVec3f(0.04, 0.04, 0.04);
    this->targetSize = targetSize;
    this->marginSize = marginSize;
    mainSize = ofVec3f(0, 0, 0);
    wSize = ofVec3f(0.01, 0.01, 0.01);
    this->ang = ang;
    this->dAng = dAng;
    offsetP = ofVec3f(ofRandom(100), ofRandom(100), ofRandom(100));
    offsetS = ofVec3f(ofRandom(100), ofRandom(100), ofRandom(100));
    this->color = color;
    this->pan = pan;
}

//---------
void Cube::draw() {
    mainPosition += pan;
    
    // update position
    ofVec3f mp = ofVec3f(marginPosition.x * sin(wPosition.x * ofGetFrameNum() + offsetP.x),
                         marginPosition.y * sin(wPosition.y * ofGetFrameNum() + offsetP.y),
                         marginPosition.z * sin(wPosition.z * ofGetFrameNum() + offsetP.z));
    ofVec3f position = mainPosition + mp;
    
    // update size
    mainSize = mainSize * 0.99 + targetSize * 0.01;
    ofVec3f ms = ofVec3f(marginSize.x * sin(wSize.x * ofGetFrameNum() + offsetS.x),
                         marginSize.y * sin(wSize.y * ofGetFrameNum() + offsetS.y),
                         marginSize.z * sin(wSize.z * ofGetFrameNum() + offsetS.z));
    ms *= (ms.length() / targetSize.length());
    ofVec3f size = mainSize + ms;
    
    // update angle
    ang += dAng;
    
    
    // draw
    ofPushMatrix();
    
    ofTranslate(position.x, position.y, position.z);
    ofRotateYDeg(-46);
    ofRotateXDeg(ang.x);
    ofRotateYDeg(ang.y);
    ofRotateZDeg(ang.z);
    
    ofFill();
    ofSetColor(color);
    ofDrawBox(0, 0, 0, size.x, size.y, size.z);
    
    ofNoFill();
    ofSetColor(0, 180);
    ofDrawBox(0, 0, 0, size.x, size.y, size.z);
    
    ofPopMatrix();
}


//---------
void Cubes::initialize() {
    setName("Cubes");
    
    bPreset1.addListener(this, &Cubes::preset1);
    bPreset2.addListener(this, &Cubes::preset2);
    bPreset3.addListener(this, &Cubes::preset3);
    bPreset4.addListener(this, &Cubes::preset4);
    bPreset5.addListener(this, &Cubes::preset5);
    bPreset6.addListener(this, &Cubes::preset6);
    bPreset7.addListener(this, &Cubes::preset7);

    gui.add(newBoxRate.set("newBoxRate", 3, 1, 10));
    gui.add(pan.set("pan", ofVec3f(-8, -3, 0), ofVec3f(-20, -20, -20), ofVec3f(20, 20, 20)));
    gui.add(translation.set("translation", ofVec2f(0, 0), ofVec2f(0, 0), ofVec2f(width, height)));
    gui.add(color.set("color", ofColor(255, 80)));
    gui.add(colorVar.set("colorVar", 10, 0, 200));
    gui.add(bPreset1.setup("preset 1"));
    gui.add(bPreset2.setup("preset 2"));
    gui.add(bPreset3.setup("preset 3"));
    gui.add(bPreset4.setup("preset 4"));
    gui.add(bPreset5.setup("preset 5"));
    gui.add(bPreset6.setup("preset 6"));
    gui.add(bPreset7.setup("preset 7"));
    
    preset1();
}

//---------
void Cubes::update() {
    translation.set(ofVec2f(ofLerp(translation->x, ofGetMouseY(), 0.01),
                            ofLerp(translation->y, ofGetMouseX(), 0.01)));
    
    if (ofGetFrameNum() % newBoxRate == 0) {
        addNewBox();
    }
}

//---------
void Cubes::drawInner() {
    ofRotateXRad(ofMap(ofNoise(0.002*ofGetFrameNum()+5), 0, 1, -0.5, 0.5));
    ofRotateYRad(ofMap(ofNoise(0.002*ofGetFrameNum()+15), 0, 1, -0.5, 0.5));
    ofRotateZRad(ofMap(ofNoise(0.002*ofGetFrameNum()+25), 0, 1, -0.5, 0.5));
    ofTranslate(width/2, translation->x, translation->y);
    
    for (int i=0; i<cubes.size(); i++) {
        cubes[i].draw();
    }
}

//---------
void Cubes::addNewBox() {
    ofColor newColor = ofColor(ofClamp(color->r + ofRandom(-colorVar,colorVar), 0, 255),
                               ofClamp(color->g + ofRandom(-colorVar,colorVar), 0, 255),
                               ofClamp(color->b + ofRandom(-colorVar,colorVar), 0, 255),
                               ofClamp(color->a + ofRandom(-colorVar,colorVar), 0, 255));
    
    Cube cube;
    cube.setup(ofVec3f(panPosition.x, panPosition.y, 0) + mainPosition.get(),
               marginPosition.get(), targetSize.get(), marginSize.get(),
               ang.get(), dAng.get(), newColor, pan);
    cubes.push_back(cube);
    
    if (cubes.size() > MAXBOXES)  {
        cubes.erase(cubes.begin());
    }
}

//--------
void Cubes::resetTimeFunctions() {
    mainPosition.reset();
    marginPosition.reset();
    targetSize.reset();
    marginSize.reset();
    ang.reset();
    dAng.reset();
}

//====== preset 1 ==========//
void Cubes::preset1() {
    resetTimeFunctions();
	mainPosition.setConstant(ofVec3f(1200, 0, 0));
	mainPosition.setFunctionRandom(ofVec3f(0, 0, -1000), ofVec3f(0, 600, -900));
	targetSize.setFunctionRandom(ofVec3f(50, 300, 100), ofVec3f(200, 800, 200));
}

//====== preset 2 ==========//
void Cubes::preset2() {
    resetTimeFunctions();
	mainPosition.setConstant(ofVec3f(1200, 0, 0));
	mainPosition.setFunctionRandom(ofVec3f(0, 0, -1000), ofVec3f(0, 0, -900));
	mainPosition.setFunctionSine(ofVec3f(0, 0, 0), ofVec3f(0, 600, 0), ofVec3f(0, 0.04, 0));
	targetSize.setConstant(ofVec3f(100, 900, 140));
	dAng.setConstant(ofVec3f(1.146, 1.4325, 0.8595));
}

//====== preset 3 ==========//
void Cubes::preset3() {
    resetTimeFunctions();
	mainPosition.setConstant(ofVec3f(1200, 0, 0));
	mainPosition.setFunctionRandom(ofVec3f(0, 0, -1000), ofVec3f(0, 0, -900));
	mainPosition.setFunctionSine(ofVec3f(0, 0, 0), ofVec3f(0, 600, 0), ofVec3f(0, 0.02, 0));
	targetSize.setConstant(ofVec3f(100, 400, 70));
	marginSize.setConstant(ofVec3f(600, 0, 300));
}

//====== preset 4 ==========//
void Cubes::preset4() {
    resetTimeFunctions();
	mainPosition.setConstant(ofVec3f(1200, 300, 0));
	mainPosition.setFunctionRandom(ofVec3f(0, 0, -1000), ofVec3f(0, 0, -900));
	marginPosition.setConstant(ofVec3f(20, 100, 20));
	targetSize.setConstant(ofVec3f(100, 100, 100));
	marginSize.setConstant(ofVec3f(60, 600, 20));
	ang.setTimeCoefficient(ofVec3f(0, 1.146, 0.573));
	dAng.setConstant(ofVec3f(0.573, 0, 0));
}

//====== preset 5 ==========//
void Cubes::preset5() {
    resetTimeFunctions();
	mainPosition.setConstant(ofVec3f(1200, 300, 0));
	mainPosition.setFunctionRandom(ofVec3f(0, 0, -1000), ofVec3f(0, 0, -900));
	marginPosition.setConstant(ofVec3f(20, 100, 20));
	targetSize.setConstant(ofVec3f(0, 400, 1));
	targetSize.setFunctionSine(ofVec3f(-400, 0, 0), ofVec3f(400, 0, 0), ofVec3f(0.2, 0, 0));
	marginSize.setConstant(ofVec3f(300, 20, 30));
	ang.setConstant(ofVec3f(45.84, 0, 0));
	dAng.setFunctionSine(ofVec3f(-1.146, 0, 0), ofVec3f(1.146, 0, 0), ofVec3f(0.01, 0, 0));
}

//====== preset 6 ==========//
void Cubes::preset6() {
    resetTimeFunctions();
	mainPosition.setConstant(ofVec3f(1200, 0, 0));
	mainPosition.setFunctionSine(ofVec3f(0, -200, -850), ofVec3f(0, 200, -450), ofVec3f(0, 0.1, 0.1));
	targetSize.setConstant(ofVec3f(130, 0, 160));
	marginSize.setFunctionSine(ofVec3f(0, -500, 0), ofVec3f(0, 500, 0), ofVec3f(0, 0.01, 0));
	ang.setConstant(ofVec3f(45.84, 0, 0));
	dAng.setConstant(ofVec3f(0, 0, 0));
	dAng.setFunctionSine(ofVec3f(-1.146, 0, 0), ofVec3f(1.146, 0, 0), ofVec3f(0.01, 0, 0));
}

//====== preset 7 ==========//
void Cubes::preset7() {
    resetTimeFunctions();
	mainPosition.setConstant(ofVec3f(1200, 300, 0));
	mainPosition.setFunctionRandom(ofVec3f(0, 0, -1000), ofVec3f(0, 0, -900));
	mainPosition.setFunctionSine(ofVec3f(0, 0, 0), ofVec3f(0, 0, 0), ofVec3f(0, 0, 0));
	marginPosition.setFunctionSine(ofVec3f(0, -800, 0), ofVec3f(0, 800, 0), ofVec3f(0, 0.02, 0));
	targetSize.setConstant(ofVec3f(130, 500, 160));
	ang.setConstant(ofVec3f(45.84, 0, 0));
	dAng.setConstant(ofVec3f(0, 0, 5.73));
}
