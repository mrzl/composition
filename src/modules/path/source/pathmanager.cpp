//
// Created by mar on 23.07.17.
//

#include "path/pathmanager.h"

#include "boost/filesystem.hpp"
#include "csv.h"

pathmanager::pathmanager() {

}

pathmanager::~pathmanager() {

}

int pathmanager::load(std::string directory, unsigned int max) {
    boost::filesystem::path dir_path(directory);
    boost::filesystem::directory_iterator end_itr;

    for (boost::filesystem::directory_iterator itr(dir_path); itr != end_itr; ++itr) {
        // If it's not a directory, list it. If you want to list directories too, just remove this check.
        if (is_regular_file(itr->path())) {
            // assign current file name to current_file and echo it out to the console.
            std::string current_file = itr->path().string();

            io::CSVReader<4> in(current_file);
            in.read_header(io::ignore_extra_column, "index", "millis", "x", "y");
            int index; long millis; int x; int y;
            path new_path;
            while(in.read_row(index, millis, x, y)){
                new_path.add_raw(millis, x, y);
            }

            m_paths.push_back(new_path);
            if(size() >= max)
            {
                break;
            }
        }
    }

    return this->size();
}

int pathmanager::size() {
    return m_paths.size();
}

int pathmanager::remove_double_clicks() {
    return filter_self_amount_of_points(3);
}

int pathmanager::filter_self_amount_of_points(int number_of_points) {
    int counter = 0;

    for(auto it2 = m_paths.begin(); it2 != m_paths.end();)
    {
        if(it2->size() <= number_of_points)
        {
            it2 = m_paths.erase(it2);
            counter++;
        }
        else
        {
            ++it2;
        }
    }

    return counter;
}

void pathmanager::clear() {
    m_paths.clear();
}

int pathmanager::filter_self_bounding_box( rect bounding_box ) {
    int counter = 0;

    for(auto it = m_paths.begin(); it != m_paths.end();)
    {
        if(!it->inside(bounding_box))
        {
            it = m_paths.erase(it);
            counter++;
        }
        else
        {
            ++it;
        }
    }
    return counter;
}
