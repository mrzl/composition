#include <graphics/ofPolyline.h>
#include "path_renderer.h"

void path_renderer::render( path p ) {
	ofPolyline cur;
	cur.setClosed(false);
	for( auto& point : p.pairs() )
	{
		cur.curveTo(point.x, point.y);
	}

	cur.draw();
}
