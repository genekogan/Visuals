#include "MoviePlayer.h"

//--------
void MoviePlayer::initialize() {
    setName("MoviePlayer");
    
    playing = false;
    speed = 1.0f;
    oldSpeed = speed;
    alpha = 255;

    // this needs to be not hardcoded...
    player.resize(10);
    img.resize(10);
    
    idxLoad = 0;
    idxImgLoad = 0;

    setupControl();
}

//--------
void MoviePlayer::setupControl() {

    bJump.addListener(this, &MoviePlayer::jumpBack);
    bRandom.addListener(this, &MoviePlayer::jumpRandom);
    bLoad.addListener(this, &MoviePlayer::selectMedia);
    bNext.addListener(this, &MoviePlayer::triggerCallback);

    moviePath.setName("movie");

    gui.add(speed.set("speed", 1.0, -3.0, 3.0));
    gui.add(alpha.set("alpha", 255, 0.0, 255.0));
    
    gui.add(bJump.setup("jump"));
    gui.add(bRandom.setup("random"));
    gui.add(bLoad.setup("load"));
    gui.add(bNext.setup("next"));
    gui.add(moviePath.set("(none)"));
    
    bool clipsHidden = false;
    if (!clipsHidden) {
        vector<string> mPaths, iPaths;
        for (int i=0; i<moviePaths.size(); i++) {
            mPaths.push_back(moviePaths[i]);
        }
        for (int i=0; i<imagePaths.size(); i++) {
            iPaths.push_back(imagePaths[i]);
        }
//        control.addMenu("movies", mPaths, this, &MoviePlayer::chooseMovie);
//        control.addMenu("images", iPaths, this, &MoviePlayer::chooseImage);
    }
    
    moviePath.addListener(this, &MoviePlayer::eMovieNameChanged);
}

//--------
void MoviePlayer::eMovieNameChanged(string & p) {
    loadMovie(moviePath);
}

//--------
void MoviePlayer::selectMedia() {
    ofFileDialogResult file = ofSystemLoadDialog();
    if (file.bSuccess) {
        vector<string> fileSplit = ofSplitString(file.filePath, ".");
        string extension = ofToLower(fileSplit[fileSplit.size()-1]);
        if (extension == "png" || extension == "jpg" || extension == "jpeg") {
            loadImage(file.filePath);
        }
        else if (extension == "mov" || extension == "mp4"){
            //loadMovie(file.filePath);
            moviePath.set(file.filePath);
        }
    }
}

//--------
void MoviePlayer::loadMovie(string path) {

    mode = MOVIE;
    playing = true;
    
    //ofVideoPlayer newPlayer;
    
    //newPlayer.loadMovie(path);
    
    /*
    for (int i=0; i<player.size(); i++) {
        player[active].stop();
    }*/
    
    /*
    newPlayer.setLoopState(OF_LOOP_NORMAL);
    newPlayer.play();
    newPlayer.update();
    newPlayer.setPaused(true);
     */
    
    
    //player[idx].push_back(newPlayer);
    //player[idxLoad] = newPlayer;
    
    
    player[idxLoad].load(path);
    player[idxLoad].setVolume(0);
    player[idxLoad].setLoopState(OF_LOOP_NORMAL);
    player[idxLoad].play();
    player[idxLoad].update();
    //player[idxLoad].setPaused(true);
    
    
    //player[idx].push_back(newPlayer);
    //player[idxLoad] = newPlayer;
    
    
    idxLoad++;
    moviePaths.push_back(path);
}

//--------
void MoviePlayer::loadImage(string path) {
    mode = IMAGE;

    playing = false;
    img[idxImgLoad].load(path);
    
    if ((float)width/height > (float)img[idxImgLoad].getWidth()/img[idxImgLoad].getHeight()) {
        h = height;
        w = img[idxImgLoad].getWidth() * h / img[idxImgLoad].getHeight();
        centeredHoriz = true;
    }
    else {
        w = width;
        h = img[idxImgLoad].getHeight() * w / img[idxImgLoad].getWidth();
        centeredHoriz = false;
    }
    
    idxImgLoad++;
    
    imagePaths.push_back(path);

}

//--------
void MoviePlayer::jumpBack() {
    player[active].setFrame(player[active].getCurrentFrame()-25);
}

//--------
void MoviePlayer::jumpRandom() {
    player[active].setFrame(ofRandom(player[active].getTotalNumFrames()));
}

//--------
void MoviePlayer::update() {
    if (!playing)   return;
    if (speed != oldSpeed) {
        player[active].setSpeed(speed);
        oldSpeed = speed;
    }
    player[active].update();
    
    ofSetWindowTitle(ofToString(ofGetFrameRate()));
}

//--------
void MoviePlayer::drawInner() {
    
    if (!(mode == MOVIE && player[active].isLoaded()) && !(mode == IMAGE && img[active].isAllocated())) {
        return;
    }
    
    ofSetColor(ofColor::white, alpha);
    
    if (mode == IMAGE) {
        if ((float)width/height > (float)img[active].getWidth()/img[active].getHeight()) {
            h = height;
            w = img[active].getWidth() * h / img[active].getHeight();
            img[active].draw(0.5 * (width - w), 0, w, h);
        }
        else {
            w = width;
            h = img[active].getHeight() * w / img[active].getWidth();
            img[active].draw(0, 0.5 * (height - h), w, h);
        }
    }
    else if (mode == MOVIE) {
        
        if ((float)width/height > (float)player[active].getWidth()/player[active].getHeight()) {
            h = height;
            w = player[active].getWidth() * h / player[active].getHeight();
            centeredHoriz = true;
        }
        else {
            w = width;
            h = player[active].getHeight() * w / player[active].getWidth();
            centeredHoriz = false;
        }

        
        if (centeredHoriz) {
            player[active].draw(0.5 * (width - w), 0, w, h);
        }
        else {
            player[active].draw(0, 0.5 * (height - h), w, h);
        }
    }
    
    ofSetColor(ofColor::white);
}

//--------
void MoviePlayer::chooseMovie(string &s) {
    for (int i=0; i<idxLoad; i++) {
        if (moviePaths[i] == s) {
            triggerMovie(i);
        }
    }
}

//--------
void MoviePlayer::chooseImage(string &s) {
    for (int i=0; i<idxImgLoad; i++) {
        if (imagePaths[i] == s) {
            triggerImage(i);
        }
    }
}

//--------
void MoviePlayer::triggerMovie(int idx) {
    //if (idx >= player.size())   return;
    if (idx >= idxLoad)   return;
    player[active].setPaused(true);
    active = idx;
    player[active].setPaused(false);
}

//--------
void MoviePlayer::triggerImage(int idx) {
    //if (idx >= player.size())   return;
    if (idx >= idxImgLoad)   return;
    active = idx;
}

//--------
void MoviePlayer::triggerMovie() {
    triggerMovie((active+1)%player.size());
}

//--------
void MoviePlayer::triggerImage() {
    triggerImage((active+1)%(idxImgLoad-1));
}

//--------
void MoviePlayer::clearMovies() {
    if (player.size() > 0) {
        player[active].stop();
    }
    
    for (int i=0; i<idxLoad; i++) {
        player[i].stop();
        player[i].close();
        player[i].closeMovie();
    }
    
    idxLoad = 0;
    
//    player.erase(player.begin(), player.end());
//    player.clear();
}


