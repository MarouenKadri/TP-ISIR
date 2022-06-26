#include "pointlight.h"

namespace RT_ISICG
{
	LightSample PointLight::sample( const Vec3f & p_point ) const
	{
		float distance	= glm::distance( _position, p_point );
		Vec3f direction = normalize( _position - p_point );
		Vec3f radiance	= _color * _power * ( 1.f / ( distance * distance ) );

		return LightSample( direction, distance, radiance, 1.f );
	}
} // namespace RT_ISICG
