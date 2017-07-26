#include "path/path.h"

path::path()
		: m_current_ms( absolute_milliseconds()) {

}

path::~path() {

}

void path::add_raw( long time_millis, int x, int y ) {
	point p{ time_millis, x, y };
	m_pairs.push_back( p );
}

int path::size() {
	return m_pairs.size();
}

std::chrono::milliseconds path::current_milliseconds() {
	return absolute_milliseconds() - m_current_ms;
}

std::chrono::milliseconds path::absolute_milliseconds() {
	std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch());
}

bool path::inside( rect r ) {
	for ( auto &p : m_pairs ) {
		if(!(p.x >= r.x() && p.x <= (r.x() + r.width()) && p.y >= r.y() && p.y <= (r.y() + r.height())))
		{
			return false;
		}
	}
	return true;
}
