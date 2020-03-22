#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //visual.setupFromJson("shader", ofGetWidth(), ofGetHeight());
    //visual.setupFromJson("startup", ofGetWidth(), ofGetHeight());


    string presetName = ofGetEnv("PRESET");
 
    string tx = ofGetEnv("X");
    string ty = ofGetEnv("Y");
    
    if (tx != "" && ty != "") {
        cout << "translate " << tx << " " << ty << endl;
        ofSetWindowPosition(ofToInt(tx), ofToInt(ty));
    }
    ofSetFullscreen(true);

    if (presetName != "") {
         visual.setupFromJson(presetName, ofGetWidth(), ofGetHeight());
    }
    visual.getScene()->setVisible(false);
    
    //visual.setupShader("blobby", "blobbylikes", ofGetWidth(), ofGetHeight());
    //visual.setupShader("blobby", "blobbylikes", ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update(){
     visual.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    visual.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' '){
        cout << "go " << endl;
        //visual.scene->getGui().loadFromFile("/Users/gene/Code/of_v0.11.0_osx_release/apps/myApps/Visuals/bin/data/presets/Scene/hello.xml");
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
