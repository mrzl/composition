//
// Created by mar on 23.07.17.
//

#include <etip.h>
#include "path/path_manager.h"

#include "boost/filesystem.hpp"
#include "csv.h"

int path_manager::load( std::string directory, unsigned int max ) {
	boost::filesystem::path dir_path( directory );
	boost::filesystem::directory_iterator end_itr;

	for ( boost::filesystem::directory_iterator itr( dir_path ); itr != end_itr; ++itr ) {
		// If it's not a directory, list it. If you want to list directories too, just remove this check.
		if ( is_regular_file( itr->path())) {
			// assign current file name to current_file and echo it out to the console.
			std::string current_file = itr->path().string();

			io::CSVReader<4> in( current_file );
			in.read_header( io::ignore_extra_column, "index", "millis", "x", "y" );
			int index;
			long millis;
			int x;
			int y;
			path new_path;
			while ( in.read_row( index, millis, x, y )) {
				new_path.add_raw( millis, x, y );
			}

			m_paths.push_back( new_path );
			if ( size() >= max && max != 0 ) {
				break;
			}
		}
	}

	return this->size();
}

int path_manager::size() {
	return m_paths.size();
}

int path_manager::remove_double_clicks() {
	auto filter = std::make_shared<amount_of_points_filter>( 3 );
	return filter_self( filter );
}


void path_manager::clear() {
	m_paths.clear();
}

path &path_manager::at( unsigned int index ) {
	return m_paths[ index ];
}

std::vector<path> &path_manager::paths() {
	return m_paths;
}

int path_manager::filter_self( std::shared_ptr<filter> f ) {
	return f->apply_self( std::make_shared<std::vector<path>>( m_paths ));
}

std::vector<path> path_manager::filter_new( std::shared_ptr<filter> f ) {
	return f->apply( m_paths );
}
