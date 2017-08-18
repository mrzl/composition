//
// Created by mar on 18.08.17.
//

#include "mouse_listener.h"

#include <iostream>
#include <future>
#include <fcntl.h>
#include <unistd.h>

mouse_listener::mouse_listener() :
		m_running( false ), m_mouse_pressed_left{ 0 }, m_mouse_pressed_middle{ 0 }, m_mouse_pressed_right{ 0 } {

	// setting up mouse button pressed stuff
	m_mouse_file = open( m_mouse_button_file_name.c_str(), O_RDWR );
	if ( m_mouse_file == -1 ) {
		std::cerr << "ERROR Opening " << m_mouse_button_file_name.c_str() << std::endl;
		std::cerr << "Did you set the right permissions? -> sudo 766 " << m_mouse_button_file_name.c_str()
				  << std::endl;
	}

	// setup mouse position stuff
	XSetWindowAttributes attribs;
	Window window;

	if (( display = XOpenDisplay( 0 ))) {
		m_running = true;
	} else {
		m_running = false;
		std::cerr << "Couldn't connect to " << XDisplayName( nullptr ) << std::endl;
	}

	attribs.override_redirect = True;
	window = XCreateWindow( display, DefaultRootWindow ( display ), -1, -1, 1, 1, 0,
							CopyFromParent, InputOnly, CopyFromParent,
							CWOverrideRedirect, &attribs );
	XMapWindow( display, window );
	XSync( display, 0 );

	// init the values once
	query_pointer( root, display );
}

mouse_listener::~mouse_listener() {
	if ( m_mouse_position_thread.joinable()) {
		m_mouse_position_thread.join();
	}

	if ( m_mouse_button_pressed_thread.joinable()) {
		m_mouse_button_pressed_thread.join();
	}
}

void mouse_listener::start() {
	m_mouse_position_thread = std::thread( [ this ]() {
		while ( m_running.load()) {
			query_pointer( root, display );
		}
	} );

	m_mouse_button_pressed_thread = std::thread( [ this ]() {
		while ( m_running.load()) {
			unsigned char data[3];
			int bytes = static_cast<int>(read( m_mouse_file, data, sizeof( data )));

			if ( bytes > 0 ) {
				int left = ( data[ 0 ] & 0x1 );
				int middle = ( data[ 0 ] & 0x4 );
				int right = ( data[ 0 ] & 0x2 );
				m_mouse_pressed_left.store( left );
				m_mouse_pressed_middle.store( middle );
				m_mouse_pressed_right.store( right );

				int x = data[ 1 ];
				int y = data[ 2 ];
				printf( "x=%d, y=%d, left=%d, middle=%d, right=%d\n", x, y, left,
						middle, right );
			}
		}
	} );
}


void mouse_listener::stop() {
	m_running.store( false );
	m_mouse_position_thread.join();
	m_mouse_button_pressed_thread.join();
}

void mouse_listener::query_pointer( Window &root, Display* display ) {

	int i, x, y;
	unsigned m;
	Window w;

	root = DefaultRootWindow( display );

	if ( !XQueryPointer( display, root, &root, &w, &x, &y, &i, &i, &m )) {
		for ( i = -1; ++i < ScreenCount( display ); ) {
			if ( root == RootWindow( display, i )) {
				break;
			}
		}
	}

	Screen* scrn = DefaultScreenOfDisplay( display );

	if ( x > scrn->width || y > scrn->height ) {
		std::cout << "bullshit" << std::endl;
	}

	m_mouse_x.store( x );
	m_mouse_y.store( y );
	m_screen_height.store( scrn->height );
	m_screen_width.store( scrn->width );
}

int mouse_listener::x() const {
	return m_mouse_x.load();
}

int mouse_listener::y() const {
	return m_mouse_y.load();
}

int mouse_listener::w() const {
	return m_screen_width.load();
}

int mouse_listener::h() const {
	return m_screen_height.load();
}

void mouse_listener::mouse_button_callback( std::function<void()> &callback ) {
	m_mouse_click_callback = callback;
}
