#include "implicit_surface.h"

namespace RT_ISICG
{
	class ImplicitSphere : public ImplicitSurface
	{
	  public:
		ImplicitSphere( const std::string & p_name, const Vec3f & p_center, const float p_radius )
			: ImplicitSurface( p_name ), _center( p_center ), _radius( p_radius )
		{
		}

		inline float _sdf( const Vec3f & p_point ) const { return glm::distance( p_point, _center ) - _radius; }

	  private:
		Vec3f _center = VEC3F_ZERO;
		float _radius = 1.f;
	};
} // namespace RT_ISICG