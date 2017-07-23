//
// Created by mar on 23.07.17.
//

#include <thread>
#include <boost/filesystem/operations.hpp>
#include "gtest/gtest.h"
#include "path/path.h"
#include "path/pathmanager.h"


TEST(path_test, relative_milliseconds)
{
    path p;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    EXPECT_EQ(p.current_milliseconds().count(), 100);
}

TEST(path_manager_test, load_some_paths)
{
    pathmanager m;
    int paths_loaded = m.load("/home/mar/code/composition/data/testing/");

    EXPECT_EQ(paths_loaded, m.size());
    EXPECT_EQ(paths_loaded, 3);
}

TEST(path_manager_test, remove_double_clicks)
{
    pathmanager m;
    m.load("/home/mar/code/composition/data/testing/");

    int removed = m.remove_double_clicks();

    EXPECT_EQ(removed, 1);
}