#include "Letters.h"


//---------
const char * Letters::alphanum = {
    "0123456789ABCDEFGHIJKLMNOPQR"
    "STUVWXYZabcdefghijklmnopqrst"
    "uvwxyz!@#$%^&*()_+;<>?~`"};

//---------
void Letters::initialize() {
    setName("Letters");
    
    gui.add(nrows.set("rows", 30, 2, 200));
    gui.add(ncols.set("cols", 40, 2, 200));
    gui.add(letterRange.set("letterRange", ofVec2f(0, 1), ofVec2f(0, 0), ofVec2f(1,1)));
    gui.add(color.set("color", ofColor(0, 255, 20)));
    gui.add(rate.set("rate", 1, 1, 10));
    gui.add(density.set("density", 0.5, 0.0f, 1.0));
    gui.add(rateNoise.set("rateNoise", ofVec2f(0.1, 0.1), ofVec2f(0, 0), ofVec2f(0.1, 0.1)));
    gui.add(rateNoiseTime.set("rateNoiseTime", 0.1, 0.0, 1.0));
    gui.add(letterNoise.set("letterNoise", ofVec2f(0.1, 0.1), ofVec2f(0, 0), ofVec2f(0.1, 0.1)));
    gui.add(letterNoiseTime.set("letterNoiseTime", 0.1, 0.0, 1.0));
    gui.add(noisyLetters.set("noisyLetters", false));
    gui.add(chinese.set("chinese", false));
    
    update();
}

//---------
void Letters::update() {
    if (chars.size() != nrows * ncols) {
        chars.resize(nrows * ncols);
        charsC.resize(nrows * ncols);
        font.load("fonts/AndaleMono.ttf", (int) height / nrows);
        fontC.load("fonts/Chinese4.ttf", 0.72 * (int) height / nrows, true, true, true);
    }
    
    if (ofGetFrameNum() % rate == 0) {
        int idx = 0;
        float noiseX;
        for (int i=0; i<ncols; i++) {
            for (int j=0; j<nrows; j++) {
                if (ofNoise(rateNoise->x*i, rateNoise->y*j, rateNoiseTime * ofGetFrameNum()) < density) {
                    if (noisyLetters) {
                        noiseX = ofNoise(letterNoise->x*i, letterNoiseTime * ofGetFrameNum(), letterNoise->y*j);
                        chars[idx] = alphanum [ (int) ofMap(noiseX, 0, 1, 81*letterRange->x, 81*letterRange->y) ];
                        charsC[idx] = 38 + (int) ofMap(noiseX, 0, 1, 86 * letterRange->x, 86 * letterRange->y);
                    }
                    else {
                        chars[idx] = alphanum[ (int) ofRandom(81 * letterRange->x, 81 * letterRange->y) ];
                        charsC[idx] = 38 + (int) ofRandom(86 * letterRange->x, 86 * letterRange->y);
                    }
                }
                idx++;
            }
        }
    }
}

//---------
void Letters::drawInner() {
    int idx = 0;
    float x, y;
    for (int i=0; i<ncols; i++) {
        for (int j=0; j<nrows; j++) {
            x = ofMap(i, 0, ncols, 0, width);
            y = ofMap(j, 0, nrows, 0, height);
            ofSetColor(color);
            if (chinese) {
                fontC.drawString(ofToString(char(charsC[idx++])), x, y);
            }
            else {
                font.drawString(ofToString(chars[idx++]), x, y);
            }
        }
    }
}
