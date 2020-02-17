#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFullscreen(true);
    
    agents.setup(ofGetWidth()/3, ofGetHeight()/3);
    amoeba.setup(ofGetWidth()/3, ofGetHeight()/3);
    bubbles.setup(ofGetWidth()/3, ofGetHeight()/3);
    polar.setup(ofGetWidth()/3, ofGetHeight()/3);
}

//--------------------------------------------------------------
void ofApp::update(){
    agents.update();
    amoeba.update();
    bubbles.update();
    polar.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    agents.draw(0, 0);
    amoeba.draw(ofGetWidth()/3, 0);
    bubbles.draw(2*ofGetWidth()/3, 0);
    polar.draw(0, ofGetHeight()/3);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
