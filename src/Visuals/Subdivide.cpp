#include "Subdivide.h"


//----------
Subdivision::Subdivision(int generation,
                         int x, int y,
                         int width, int height,
                         ofParameter<ofColor> & color,
                         ofParameter<ofColor> & varColor,
                         ofParameter<int> & circleResolution,
                         ofParameter<bool> & isLerp) {
    this->generation = generation;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->color = color;
    this->varColor = varColor;
    this->circleResolution = circleResolution;
    this->isLerp = isLerp;
    parent = NULL;
    subdivide();
}

//----------
Subdivision::Subdivision(int generation,
                         Subdivision *parent,
                         bool topleft,
                         ofParameter<int> & circleResolution,
                         ofParameter<bool> & isLerp) {
    this->generation = generation;
    this->parent = parent;
    this->topleft = topleft;
    this->circleResolution = circleResolution;
    this->isLerp = isLerp;
    color = ofColor::white;
    varColor = parent->varColor;
    offset = ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
    subdivide();
    update();
}

//----------
void Subdivision::subdivide() {
    if (generation > 0) {
        ratio = ofRandom(1);
        horizontal = ofRandom(1) < 0.5 ? true : false;
        child1 = new Subdivision(generation-1, this, true, circleResolution, isLerp);
        child2 = new Subdivision(generation-1, this, false, circleResolution, isLerp);
    }
}

//----------
void Subdivision::update() {
    int r, g, b;
    if (parent == NULL) return;
    if (parent->horizontal) {
        x = parent->x + (topleft ? 0.0 : parent->width * parent->ratio);
        y = parent->y;
        width = parent->width * (topleft ? parent->ratio : 1.0 - parent->ratio);
        height = parent->height;
    }
    else {
        y = parent->y + (topleft ? 0.0 : parent->height * parent->ratio);
        x = parent->x;
        width = parent->width;
        height = parent->height * (topleft ? parent->ratio : 1.0-parent->ratio);
    }
    if (isLerp) {
        r = ofClamp(ofLerp(color->r, parent->color->r +
                           varColor->r * 0.2 * offset.x, 0.2), 0, 255);
        g = ofClamp(ofLerp(color->g, parent->color->g +
                           varColor->g * 0.2 * offset.y, 0.2), 0, 255);
        b = ofClamp(ofLerp(color->b, parent->color->b +
                           varColor->b * 0.2 * offset.z, 0.2), 0, 255);
    }
    else {
        r = parent->color->r + varColor->r * offset.x;
        g = parent->color->g + varColor->g * offset.y;
        b = parent->color->b + varColor->b * offset.z;
    }
    color.set(ofColor(r, g, b));
}

//----------
void Subdivision::draw(DrawStrategy drawStrategy) {
    update();
    
    ofSetCircleResolution(circleResolution);
    ofEnableSmoothing();
    
    if (generation == 0) {
        if (drawStrategy == RECTS) {
            drawRect();
        }
        else if (drawStrategy == DIAMONDS) {
            drawDiamond();
        }
        else if (drawStrategy == CIRCLES) {
            drawCircle();
        }
    }
    else {
        child1->draw(drawStrategy);
        child2->draw(drawStrategy);
    }
    
    ofDisableSmoothing();
}

//----------
void Subdivision::drawRect() {
    ofSetColor(color);
    ofFill();
    ofDrawRectangle(x, y, width, height);
    ofNoFill();
    ofSetColor(0);
    ofSetLineWidth(1);
    ofDrawRectangle(x, y, width, height);
}

//----------
void Subdivision::drawDiamond() {
    ofSetColor(color);
    ofFill();
    ofBeginShape();
        ofVertex(x, y+height/2);
        ofVertex(x+width/2, y);
        ofVertex(x+width, y+height/2);
        ofVertex(x+width/2, y+height);
    ofEndShape();
    ofNoFill();
    ofSetColor(0);
    ofSetLineWidth(1);
    ofBeginShape();
        ofVertex(x, y+height/2);
        ofVertex(x+width/2, y);
        ofVertex(x+width, y+height/2);
        ofVertex(x+width/2, y+height);
    ofEndShape();
}

//----------
void Subdivision::drawCircle() {
    ofSetColor(color);
    ofFill();
    ofDrawEllipse(x+width/2, y+height/2, width, height);
    ofNoFill();
    ofSetColor(0);
    ofSetLineWidth(1);
    ofDrawEllipse(x+width/2, y+height/2, width, height);
}

//----------
void Subdivide::initialize() {
    setName("Subdivide");

    gui.add(circleResolution.set("circleResolution", 10, 3, 72));
    gui.add(isLerp.set("lerp", false));
    gui.add(color.set("color", ofColor(100, 255, 120)));
    gui.add(varColor.set("varColor", ofColor(20, 20, 20)));

    vector<string> drawTypes;
    drawTypes.push_back("Rects");
    drawTypes.push_back("Diamonds");
    drawTypes.push_back("Circles");
    //control.addMenu("draw", drawTypes, this, &Subdivide::setDrawType);

    start = new Subdivision(9, 0, 0, width, height, color, varColor, circleResolution, isLerp);
}

//----------
void Subdivide::setDrawType(string & s) {
    if (s=="Rects") {
        drawStrategy = RECTS;
    }
    else if (s=="Diamonds") {
        drawStrategy = DIAMONDS;
    }
    else if (s=="Circles") {
        drawStrategy = CIRCLES;
    }
}

//----------
void Subdivide::update() {
    
}

//----------
void Subdivide::drawInner() {
    start->draw(drawStrategy);
}
