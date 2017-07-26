#include <thread>
#include <boost/filesystem/operations.hpp>
#include <gmock/gmock-matchers.h>
#include "gtest/gtest.h"
#include "path/path.h"
#include "path/pathmanager.h"

using ::testing::_;

class PathManagerTest : public ::testing::Test {
public:
	PathManagerTest() : m_recordings_path( "/home/mar/code/composition/data/testing/" ) {

	}

	std::string m_recordings_path;
};

TEST( path_test, relative_milliseconds ) {
	path p;
	std::this_thread::sleep_for( std::chrono::milliseconds( 50 ));
	EXPECT_EQ( p.current_milliseconds().count(), 50 );
}

TEST( path_test, inside ) {
	path p;
	p.add_raw( 0, 10, 10 );
	p.add_raw( 5, 10, 20 );

	bool inside = p.inside( rect( 0, 0, 50, 50 ));

	EXPECT_EQ( inside, true );
}


TEST_F( PathManagerTest, test_load_some_paths ) {
	pathmanager m;
	int paths_loaded = m.load( m_recordings_path, 2 );

	EXPECT_EQ( paths_loaded, m.size());
	EXPECT_EQ( paths_loaded, 2 );

	m.clear();
	paths_loaded = m.load( m_recordings_path, 2 );
	EXPECT_EQ( paths_loaded, 2 );
}

TEST_F( PathManagerTest, test_remove_double_clicks ) {
	pathmanager m;
	m.load( m_recordings_path );

	int removed = m.remove_double_clicks();

	EXPECT_EQ( removed, 1 );
}

TEST_F( PathManagerTest, filter_by_bounding_box ) {
	pathmanager m;
	m.load( m_recordings_path, 3 );

	int removed = m.filter_self_bounding_box( rect( 0, 0, 100, 100 ));

	EXPECT_EQ( removed, 2 );
}