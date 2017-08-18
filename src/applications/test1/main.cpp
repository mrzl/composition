#include <iostream>

#include "ofMain.h"
#include "path/path_manager.h"
#include "path_renderer.h"

class ofApp : public ofBaseApp {
public:

	int paths_loaded;
	path_manager m;

	void setup() {
		paths_loaded = m.load( "/home/mar/code/composition/data/june_2015/" );
		std::cout << paths_loaded << std::endl;
	}

	void update() {
		ofHideCursor();
	}

	void draw() {
		ofBackground( 0 );
		ofSetColor( 255 );
		ofSetWindowTitle( ofToString( ofGetFrameRate()));
		auto r = rect( ofGetMouseX(), ofGetMouseY(), 200, 200 );
		auto bb_filter = std::make_shared<bounding_box_filter>( r );
		auto paths = m.filter_new( bb_filter );
		for ( auto &path: paths ) {
			path_renderer::render( path );
		}
	}
};

int main() {
	ofSetupOpenGL( 1920, 1080, OF_FULLSCREEN );
	ofRunApp( new ofApp());
	return 0;
}
