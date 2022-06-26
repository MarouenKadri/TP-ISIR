#include "PlaneGeometry.h"

namespace RT_ISICG
{
	bool PlaneGeometry::intersect(const Ray & p_ray, float & p_t) const {
		
		p_t = glm::dot( _point - p_ray.getOrigin(), _normal ) / glm::dot( p_ray.getDirection(), _normal );
		if ( p_t > 0 ) { return true; }
		return false;
	}
}