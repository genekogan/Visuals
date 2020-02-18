#include "GridFly.h"


//-------
void GridFly::initialize(){
    setName("GridFly");

    gui.add(nx.set("nx", 100, 10, 400));
    gui.add(ny.set("ny", 100, 10, 400));
    gui.add(length.set("length", ofVec2f(2000, 2000), ofVec2f(100,100), ofVec2f(4000,4000)));
    gui.add(margin.set("margin", 100, 0.0, 1000.0));
    gui.add(noiseFactor.set("noiseFactor", ofVec2f(0.001, 0.001), ofVec2f(0, 0), ofVec2f(0.01, 0.01)));
    gui.add(speed.set("speed", 20, 0.0, 100.0));
    gui.add(angle.set("angle", 90, 0.0, 360.0));
    gui.add(axis.set("axis", ofVec3f(1, 0, 0), ofVec3f(0, -1, -1), ofVec3f(1, 1, 1)));
    gui.add(color.set("color", ofColor(255, 100)));
    
    //vertices = mesh.getVerticesPointer();
    for (int j=0; j<ny; j++) {
        addRow();
        y++;
    }
    minY = -length->y;
    dy = length->y / ny;
    y = 0;
}

//-------
void GridFly::update(){
    Z += speed;
    
    cam.resetTransform();
    cam.rotate(angle, axis->x, axis->y, axis->z);
    cam.setPosition(camPosition.x, Z, camPosition.y);
    
    /*
    if (vertices->size() > nx*ny*6) {
        vertices->erase(vertices->begin(), vertices->begin() + (vertices->size() - nx*ny));
    }
    while (cam.getPosition().y > minY) {
        vertices->erase(vertices->begin(), vertices->begin() + nx*6);
        minY = vertices->at(0).y;
        addRow();
        y++;
    }
     */
}

//-------
void GridFly::addRow() {
    for (int x=0; x<nx; x++) {
        
        float x1 = ofMap(x, 0, nx, -0.5*length->x, 0.5*length->x);
        float x2 = ofMap(x+1, 0, nx, -0.5*length->x, 0.5*length->x);
        float y1 = ofMap(y, 0, ny, -length->y, 0);
        float y2 = ofMap(y+1, 0, ny, -length->y, 0);
        
        float z11 = -margin * (-1.0 + 2.0*ofNoise(noiseFactor->x * x1, noiseFactor->y * y1));
        float z12 = -margin * (-1.0 + 2.0*ofNoise(noiseFactor->x * x1, noiseFactor->y * y2));
        float z21 = -margin * (-1.0 + 2.0*ofNoise(noiseFactor->x * x2, noiseFactor->y * y1));
        float z22 = -margin * (-1.0 + 2.0*ofNoise(noiseFactor->x * x2, noiseFactor->y * y2));
        
        mesh.addVertex(ofVec3f(x1, y1, z11));
        mesh.addVertex(ofVec3f(x2, y1, z21));
        mesh.addVertex(ofVec3f(x2, y2, z22));
        
        mesh.addVertex(ofVec3f(x1, y1, z11));
        mesh.addVertex(ofVec3f(x1, y2, z12));
        mesh.addVertex(ofVec3f(x2, y2, z22));
    }
}

//-------
void GridFly::drawInner(){
    ofNoFill();
    ofSetColor(color);
    cam.begin();
    mesh.drawWireframe();
    cam.end();
}

//-------
GridFly::~GridFly(){
    cam.disableOrtho();
    cam.disableMouseMiddleButton();
    cam.disableMouseInput();
    ofRemoveListener(ofEvents().update, (Scene*) this, &Scene::update);
}
