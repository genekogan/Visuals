#pragma once

#include "ofMain.h"
#include "ofxGui.h"


class Scene
{
public:
    
    Scene() {
        width = ofGetWidth();
        height = ofGetHeight();
        name = "Scene";
        gui.clear();
        gui.setup("Scene");
        gui.add(toClear.set("clear", false));
        gui.add(upsideDown.set("upsideDown", false));
        gui.add(bgColor.set("bgColor", ofColor::black));
        setVisible(true);
    }
    
    virtual ~Scene() {
        ofRemoveListener(ofEvents().update, this, &Scene::update);
    }
    
    void setName(string name) {
        this->name = name;
        gui.setName(name);
        toClear = false;
    }
        
    string getName() {
        return name;
    }
    
    void setup(int width, int height) {
        this->width = width;
        this->height = height;
        fbo.allocate(width, height, GL_RGBA);
        initialize();
    }

    virtual void initialize() {
        
    }

    void update(ofEventArgs &data) {
        update();
    }

    virtual void update() {
        
    }

    void updateFBO() {
        
        fbo.begin();

        if (toClear) {
            ofClear(0, 0);
            toClear = false;
        }

        ofPushMatrix();
        ofPushStyle();
        
        ofEnableSmoothing();
        
        if (bgColor->a > 0) {
            ofFill();
            ofSetColor(bgColor);
            ofDrawRectangle(0, 0, width, height);
        }

        ofSetColor(ofColor::white);

        drawInner();     // call draw method of subclass
        
        ofDisableSmoothing();
        
        ofPopStyle();
        ofPopMatrix();
        
        fbo.end();
    }
    
    void draw(int x, int y) {
        updateFBO();
        
        ofPushMatrix();
        ofPushStyle();

        ofTranslate(x, y);
        
        if (upsideDown) {
            ofTranslate(width, height);
            ofRotateDeg(180);
        }

        fbo.draw(0, 0);

        ofPopStyle();
        ofPopMatrix();

        if (guiVisible) {
            gui.draw();
        }
    }

    virtual void drawInner() {
        
    }

    void setAutoUpdate(bool autoUpdate) {
        this->autoUpdate = autoUpdate;
        if (autoUpdate) {
            ofAddListener(ofEvents().update, this, &Scene::update);
        } else {
            ofRemoveListener(ofEvents().update, this, &Scene::update);
        }
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
    
    ofxPanel & getGui() {
        return gui;
    }

protected:
    
    ofxPanel gui;
    bool guiVisible;
    
    string name;
    int width;
    int height;
    bool autoUpdate;
    
    ofParameter<ofColor> bgColor;
    ofParameter<bool> toClear;
    ofParameter<bool> upsideDown;
    
    ofFbo fbo;
};

