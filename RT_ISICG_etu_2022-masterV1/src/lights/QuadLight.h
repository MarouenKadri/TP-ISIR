#pragma once
#include "base_light.hpp"

namespace RT_ISICG
{
	class QuadLight : public BaseLight
	{
	  public:
		QuadLight()			 = delete;
		virtual ~QuadLight() = default;

		QuadLight( const Vec3f & p_position,
				   const Vec3f & p_u,
				   const Vec3f & p_v,
				   const Vec3f & p_color,
				   const float	 p_power )
			: BaseLight( p_color, p_power, true ), _position( p_position ), _u( p_u ), _v( p_v )
		{
			_normal = glm::normalize( glm::cross( _u, _v ) );

			float angle = glm::acos( glm::dot( glm::normalize( _u ), glm::normalize( _v ) ) );

			float hauteur = glm::length( _v ) * glm::sin( angle );

			_area = glm::length( _u ) * hauteur;
		}

		virtual LightSample sample( const Vec3f & p_point ) const override;

	  private:
		Vec3f _position = VEC3F_ZERO;
		Vec3f _u		= VEC3F_ZERO;
		Vec3f _v		= VEC3F_ZERO;
		Vec3f _normal	= VEC3F_ZERO;
		float _area		= 0.f;
	};
} // namespace RT_ISICG