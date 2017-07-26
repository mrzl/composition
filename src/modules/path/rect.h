#pragma once

class rect
{
public:
    rect(unsigned int x, unsigned int y, unsigned int width, unsigned int height);

	unsigned int x();
	unsigned int y();
	unsigned int width();
	unsigned int height();

	void x(unsigned int x);
	void y(unsigned int y);
	void width(unsigned int width);
	void height(unsigned int height);
private:
    unsigned int m_x, m_y, m_w, m_h;
};