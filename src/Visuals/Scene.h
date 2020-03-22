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

        bSave.addListener(this, &Scene::eSaveSettings);
        bLoad.addListener(this, &Scene::eLoadSettings);

        gui.clear();
        gui.setup("Scene");
        gui.add(bSave.setup("save settings"));
        gui.add(bLoad.setup("load settings"));
        gui.add(toClear.set("clear", false));
        gui.add(upsideDown.set("upsideDown", false));
        gui.add(bgColor.set("bgColor", ofColor::black));

        setVisible(true);
    }
    
    virtual ~Scene() {
        setAutoUpdate(false);
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

    void loadSettings(string path) {
        cout << "LOAD FROM " << path << endl;
        gui.loadFromFile(path);
    }

    void loadPreset(string presetName) {
        string presetDir = "presets/"+name;
        string path = presetDir+"/"+presetName+".xml";
        loadSettings(path);
    }

    void eLoadSettings() {
        ofFileDialogResult file = ofSystemLoadDialog();
        if (file.bSuccess) {
            vector<string> fileSplit = ofSplitString(file.filePath, ".");
            string extension = ofToLower(fileSplit[fileSplit.size()-1]);
            if (extension == "xml") {
                loadSettings(file.filePath);
            }
            else {
                ofLog(OF_LOG_ERROR, "file is not an xml file");
            }
        }
    }
    
    void saveSettings(string path) {
        gui.saveToFile(path);
    }
    
    void savePreset(string presetName) {
        string presetDir = "presets/"+name;
        string path = presetDir+"/"+presetName+".xml";
        saveSettings(path);
    }

    void eSaveSettings() {
        ofDirectory dir;

        string presetDir = "presets/"+name;
        string presetName = ofSystemTextBoxDialog("What is the name of this preset?");
        string path = presetDir+"/"+presetName+".xml";
        
        dir.open("presets");
        if(!dir.exists()){
            dir.createDirectory("presets");
        }
        dir.open(presetDir);
        if(!dir.exists()){
            dir.createDirectory(presetDir);
        }
        
        saveSettings(path);
    }

protected:
    
    ofxPanel gui;
    bool guiVisible;
    ofxButton bSave, bLoad;

    string name;
    int width;
    int height;
    bool autoUpdate;
    
    ofParameter<ofColor> bgColor;
    ofParameter<bool> toClear;
    ofParameter<bool> upsideDown;
    
    ofFbo fbo;
};

