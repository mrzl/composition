//
// Created by mar on 23.07.17.
//

#include "gtest/gtest.h"
#include "path/path.h"

/*
int main(int ac, char* av[])
{
    testing::InitGoogleTest(&ac, av);
    return RUN_ALL_TESTS();
}
*/

TEST(path_test, initialization)
{
    path p;
    EXPECT_TRUE(true);
}