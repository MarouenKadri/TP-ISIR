#pragma once
#include "./base_geometry.hpp"

namespace RT_ISICG 
{
	class PlaneGeometry : public BaseGeometry
	{
	  public:
		PlaneGeometry()		  = delete;
		virtual ~PlaneGeometry() = default;

		PlaneGeometry( const Vec3f & p_point, const Vec3f & p_normal ) : _point( p_point ), _normal( normalize(p_normal) ) {}

		inline const Vec3f & getNormal() const { return _normal; }
		inline const Vec3f & getPoint() const { return _point; }

		bool intersect( const Ray & p_ray, float & p_t) const;

	  private:
		Vec3f _normal;
		Vec3f _point;
	};
}
