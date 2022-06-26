#include "QuadLight.h"
#include "utils/random.hpp"

namespace RT_ISICG
{
	LightSample QuadLight::sample( const Vec3f & p_point ) const
	{
		Vec3f random_position = _position + _u * randomFloat() + _v * randomFloat();

		Vec3f direction = normalize( random_position - p_point );
		float distance	= glm::distance( p_point, random_position );
		float dot_dir	= glm::dot( _normal, direction );
		if ( dot_dir <= 0.f ) { return LightSample( direction, distance, VEC3F_ZERO, 1.f ); }
		float pdf	   = ( distance * distance ) / ( _area * dot_dir );
		Vec3f radiance = _color * _power / pdf;

		return LightSample( direction, distance, radiance, pdf );
	}
} // namespace RT_ISICG