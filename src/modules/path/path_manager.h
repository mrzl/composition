#pragma once

#include "path.h"
#include "rect.h"
#include "filter.h"

#include <vector>
#include <string>
#include <iostream>
#include <memory>

class path_manager {
public:
	std::vector<path>& paths();
	int load( std::string directory, unsigned int max = 0 );
	int size();
	path& at(unsigned int index);
	void clear();
	int remove_double_clicks();
	int filter_self(std::shared_ptr<filter> f);
	std::vector<path> filter_new(std::shared_ptr<filter> f);

private:
	std::vector<path> m_paths;
};