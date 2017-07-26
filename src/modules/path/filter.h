#pragma once

#include "path/path.h"
#include "path/rect.h"

#include <memory>

class filter {
public:
	virtual int apply_self( std::shared_ptr<std::vector<path>> paths ) = 0;
	virtual std::vector<path> apply(std::vector<path>& paths) = 0;
};

class bounding_box_filter : public filter {
public:
	bounding_box_filter(rect r);
	int apply_self( std::shared_ptr<std::vector<path>> paths );
	std::vector<path> apply(std::vector<path>& paths );

private:
	rect m_rect;
};

class amount_of_points_filter : public filter {
public:
	amount_of_points_filter(unsigned int max_points);

	int apply_self( std::shared_ptr<std::vector<path>> paths );
	std::vector<path> apply(std::vector<path>& paths );

private:
	unsigned int m_max_points;
};