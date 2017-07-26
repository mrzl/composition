#include <gmock/gmock-matchers.h>
#include "gtest/gtest.h"

#include "path/rect.h"

using ::testing::_;

TEST( geom_test, rectBasic ) {
	rect r( 0, 1, 100, 101 );

	EXPECT_EQ( r.x(), 0 );
	EXPECT_EQ( r.y(), 1 );
	EXPECT_EQ( r.width(), 100 );
	EXPECT_EQ( r.height(), 101 );
}