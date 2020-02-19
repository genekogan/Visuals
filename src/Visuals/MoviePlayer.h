#pragma once

#include "ofMain.h"
#include "Scene.h"



class MoviePlayer : public Scene
{
public:
    enum MediaMode { IMAGE, MOVIE };
    
    void initialize();
    void update();
    void drawInner();

    void loadMovie(string path);
    void loadImage(string path);
    
    void jumpBack();
    void jumpRandom();
    void selectMedia();
    void chooseMovie(string &s);
    void chooseImage(string &s);
    
    void triggerImage(int idx);
    void triggerImage();
    void triggerMovie(int idx);
    void triggerMovie();
    void triggerCallback() { mode == MOVIE ? triggerMovie() : triggerImage(); }

    void clearMovies();
    void setupControl();
    
private:
    
    vector<ofVideoPlayer> player;
    vector<string> moviePaths, imagePaths;
    int active;
    
    //ofImage img;
    vector<ofImage> img;
    
    int w, h;
    ofParameter<float> speed;
    float oldSpeed;
    bool playing;
    
    MediaMode mode;
    bool centeredHoriz;
    
    ofParameter<float> alpha;
    
    int idxLoad;
    int idxImgLoad;
        
    ofxButton bJump;
    ofxButton bRandom;
    ofxButton bLoad;
    ofxButton bNext;
    
    
    
    
    void eMovieNameChanged(string & path);
    ofParameter<string> moviePath;
};



