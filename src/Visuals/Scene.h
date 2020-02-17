#pragma once

#include "ofMain.h"
#include "ofxGui.h"
//#include "Control.h"


class Scene
{
public:
    Scene() {
//        ofAddListener(ofEvents().update, this, &Scene::update);
//        control.setVisible(false);
        width = ofGetWidth();
        height = ofGetHeight();
        name = "Scene";
        upsideDown = false;
        active = false;
        gui.setup("Scene");
    }
    
    virtual ~Scene() {
        ofRemoveListener(ofEvents().update, this, &Scene::update);
    }

    string getName() {
        return name;
    }
    
    void setName(string name) {
        this->name = name;
        gui.setName(name);
        bgColor.set(0, 0, 0, 255);
//        control.setName(name);
//        control.clear();
//        control.addParameter("clear", &toClear);
//        control.addColor("bgColor", &bgColor);
        toClear = false;
    }
        
    virtual void initialize() { }

    virtual void update() { }
    
    virtual void drawInner() { }
    
    void setup(int width, int height) {
        this->width = width;
        this->height = height;
        active = true;
        initialize();
    }
    
    void update(ofEventArgs &data) {
        if (active) {
            update();
        }
    }
    
    void draw(int x, int y) {
        ofPushMatrix();
        ofPushStyle();
        
        ofEnableSmoothing();
        
        ofTranslate(x, y);
        
        if (upsideDown) {
            ofTranslate(width, height);
            ofRotate(180);
        }
        
        if (toClear) {
            ofClear(0, 0);
        }
        
        if (bgColor.a > 0) {
            ofFill();
            ofSetColor(bgColor);
            ofDrawRectangle(0, 0, width, height);
        }

        ofSetColor(255, 255);

        drawInner();     // call draw method of subclass
        
        ofDisableSmoothing();
        
        ofPopStyle();
        ofPopMatrix();
        
        if (guiVisible) {
            gui.draw();
        }
    }
    
    bool getActive() {
        return active;
    }

    virtual void setActive(bool active) {
        this->active = active;
//        control.setActive(active);
    }

    void setGuiPosition(int x, int y) {
        gui.setPosition(x, y);
    }

    void setVisible(bool visible) {
        this->guiVisible = visible;
    }
    
    void toggeVisible() {
        setVisible(!this->guiVisible);
    }
    
    void setUpsideDown(bool upsideDown) {
        this->upsideDown = upsideDown;
    }
    
//    Control & getControl() {
//        return control;
//    }

//    Control control;
    ofxPanel gui;
    bool guiVisible;
    string name;
    int width, height;
    ofColor bgColor;
    bool toClear;
    bool upsideDown;
    bool active;
};

