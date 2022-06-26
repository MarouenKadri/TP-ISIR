#include "sphere_geometry.hpp"

namespace RT_ISICG
{
	bool SphereGeometry::intersect( const Ray & p_ray, float & p_t1, float & p_t2 ) const
	{
		

		Vec3f oc = p_ray.getOrigin() - getCenter();
		float r	 = getRadius();
		float b	 = -dot( oc, p_ray.getDirection() );
		float c = dot( oc, oc ) - r * r;
		float delta	 = b * b - c;
		if ( delta < 0.0f ) return false;
		float s = sqrt( delta );
		p_t1	= b - s;
		p_t2	= b + s;
		return true;

	}

} // namespace RT_ISICG
