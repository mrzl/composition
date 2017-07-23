#pragma once

#include "path.h"

#include <vector>
#include <string>
#include <iostream>

class pathmanager
{
public:
    pathmanager();
    ~pathmanager();

    int load(std::string directory, unsigned int max = 100);
    int size();

    int remove_double_clicks();
    int filter_self_amount_of_points( int number_of_points );

private:
    std::vector<path> m_paths;
};