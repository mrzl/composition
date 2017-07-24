//
// Created by mar on 23.07.17.
//

#include <iostream>

#include "ofMain.h"
#include "../../modules/path/pathmanager.h"

class ofApp : public ofBaseApp {
public:

    int paths_loaded;

    void setup() {
        pathmanager m;
        paths_loaded = m.load("/home/mar/code/composition/data/testing/");
        std::cout << paths_loaded << std::endl;
    }

    void update() {
    }

    void draw() {
        ofBackground( 0 );
        ofSetColor(255),
        ofDrawBitmapString(ofToString(paths_loaded), ofGetMouseX(), ofGetMouseY());
    }
};

int main()
{
    ofSetupOpenGL(1024,768, OF_WINDOW);
    ofRunApp( new ofApp());
    return 0;
}
