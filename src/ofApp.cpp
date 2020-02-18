#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFullscreen(true);
    
    
//    agents.setup(ofGetWidth()/3, ofGetHeight()/3);
    amoeba.setup(ofGetWidth()/3, ofGetHeight()/3);
//    bubbles.setup(ofGetWidth()/3, ofGetHeight()/3);
//    cubes.setup(ofGetWidth()/3, ofGetHeight()/3);
//    debugscreen.setup(ofGetWidth()/3, ofGetHeight()/3);
//    gridfly.setup(ofGetWidth()/3, ofGetHeight()/3);
//    letters.setup(ofGetWidth()/3, ofGetHeight()/3);
//    meshy.setup(ofGetWidth()/3, ofGetHeight()/3);
//    movieplayer.setup(ofGetWidth()/2, ofGetHeight()/2);
//    polar.setup(ofGetWidth()/3, ofGetHeight()/3);
    
//    movieplayer.loadMovie("/Users/gene/bin/lapnorm/nips/NIPS_GeneKogan_new.mp4");
    
    rivers.setup(ofGetWidth()/3, ofGetHeight()/3);
    shade.setup(ofGetWidth()/3, ofGetHeight()/3);
    shapespace.setup(ofGetWidth()/3, ofGetHeight()/3);
    subdivide.setup(ofGetWidth()/3, ofGetHeight()/3);

}

//--------------------------------------------------------------
void ofApp::update(){
     amoeba.update();
//    amoeba.update();
//    bubbles.update();
//    polar.update();
//    cubes.update();
//    debugscreen.update();
//    gridfly.update();
//    letters.update();
//    meshy.update();
//    movieplayer.update();
    
    rivers.update();
    shade.update();
    shapespace.update();
    subdivide.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
//    amoeba.draw(0, 0);
//    agents.draw(0*ofGetWidth()/3, 0*ofGetHeight()/3);
//    amoeba.draw(1*ofGetWidth()/3, 0*ofGetHeight()/3);
//    bubbles.draw(2*ofGetWidth()/3, 0*ofGetHeight()/3);
//    polar.draw(0*ofGetWidth()/3, 1*ofGetHeight()/3);
//    cubes.draw(1*ofGetWidth()/3, 1*ofGetHeight()/3);
//    debugscreen.draw(2*ofGetWidth()/3, 1*ofGetHeight()/3);
//    gridfly.draw(0*ofGetWidth()/3, 2*ofGetHeight()/3);
//    letters.draw(1*ofGetWidth()/3, 2*ofGetHeight()/3);
//    meshy.draw(2*ofGetWidth()/3, 2*ofGetHeight()/3);
//    movieplayer.draw(2.5*ofGetWidth()/3, 2*ofGetHeight()/3);
    
    subdivide.draw(0, 0);
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
