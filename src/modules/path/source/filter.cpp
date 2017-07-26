#include "path/filter.h"

bounding_box_filter::bounding_box_filter( rect r )
		: m_rect( r ) {

}

int bounding_box_filter::apply_self( std::shared_ptr<std::vector<path>> paths ) {
	int size = paths->size();
	for ( auto it = paths->begin(); it != paths->end(); ) {
		if ( !it->inside( m_rect )) {
			it = paths->erase( it );
		} else {
			++it;
		}
	}

	return size - paths->size();
}

std::vector<path> bounding_box_filter::apply( std::vector<path>& paths ) {
	std::vector<path> return_paths;

	for( auto& p : paths ) {
		if ( p.inside( m_rect )) {
			return_paths.push_back( p );
		}
	}

	return return_paths;
}

amount_of_points_filter::amount_of_points_filter( unsigned int max_points )
		: m_max_points( max_points ) {

}

int amount_of_points_filter::apply_self( std::shared_ptr<std::vector<path>> paths ) {
	int size = paths->size();

	for ( auto it = paths->begin(); it != paths->end(); ) {
		if ( it->size() <= m_max_points ) {
			it = paths->erase( it );
		} else {
			++it;
		}
	}

	return size - paths->size();
}

std::vector<path> amount_of_points_filter::apply( std::vector<path>& paths ) {
	std::vector<path> return_paths;

	for( auto& p : paths){
		if ( p.size() >= m_max_points ) {
			return_paths.push_back( p );
		}
	}

	return return_paths;
}
