#include <iostream>

#include "ofMain.h"
#include "path/pathmanager.h"
#include "path_renderer.h"

class ofApp : public ofBaseApp {
public:

	int paths_loaded;
	pathmanager m;

	void setup() {
		paths_loaded = m.load( "/home/mar/code/composition/data/june_2015/" );
		std::cout << paths_loaded << std::endl;
	}

	void update() {
	}

	void draw() {
		ofBackground( 0 );
		ofSetColor( 255 );
		ofSetWindowTitle( ofToString( ofGetFrameRate()));

		auto paths = m.filter_bounding_box( rect( ofGetMouseX(), ofGetMouseY(), 200, 200 ));
		for ( auto &path: paths ) {
			path_renderer::render( path );
		}
	}
};

int main() {
	ofSetupOpenGL( 1920, 1080, OF_WINDOW );
	ofRunApp( new ofApp());
	return 0;
}
