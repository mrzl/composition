#pragma once

#include "path.h"
#include "rect.h"

#include <vector>
#include <string>
#include <iostream>

class pathmanager {
public:
	pathmanager();

	~pathmanager();

	std::vector<path>& paths();
	int load( std::string directory, unsigned int max = 0 );
	int size();
	path& at(unsigned int index);
	void clear();
	int remove_double_clicks();
	int filter_self_amount_of_points( int number_of_points );
	int filter_self_bounding_box( rect bounding_box );
	std::vector<path> filter_bounding_box(rect bounding_box);

private:
	std::vector<path> m_paths;
};