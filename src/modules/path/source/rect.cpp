#include "path/rect.h"

rect::rect( unsigned int x, unsigned int y, unsigned int width, unsigned int height )
		: m_x( x ),
		  m_y( y ),
		  m_w( width ),
		  m_h( height ) {

}

unsigned int rect::x() {
	return m_x;
}

unsigned int rect::y() {
	return m_y;
}

unsigned int rect::width() {
	return m_w;
}

unsigned int rect::height() {
	return m_h;
}

void rect::y( unsigned int y ) {
	m_y = y;
}

void rect::x( unsigned int x ) {
	m_x = x;
}

void rect::width( unsigned int width ) {
	m_w = width;
}

void rect::height( unsigned int height ) {
	m_h = height;
}
