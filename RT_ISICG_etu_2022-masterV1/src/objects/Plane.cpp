#include "Plane.h"



namespace RT_ISICG
{
	bool Plane::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const
	{
		float t;
		if (_geometry.intersect(p_ray, t)) {
			if ( t > p_tMax || t < p_tMin ) { return false; }

			p_hitRecord._point	= p_ray.pointAtT( t );
			p_hitRecord._normal = _geometry.getNormal();
			p_hitRecord.faceNormal( p_ray.getDirection() );
			p_hitRecord._distance = t;
			p_hitRecord._object	  = this;

			return true;
		}
		else
		{
			return false;
		}
	}

	bool Plane::intersectAny(const Ray& p_ray, const float p_tMin, const float p_tMax) const 
	{
		Vec3f Point1 = p_ray.getOrigin() + p_ray.getDirection() * p_tMin;
		Vec3f Point2= p_ray.getOrigin() + p_ray.getDirection() * p_tMax;

		int Flag1 = glm::dot( Point1 - _geometry.getPoint(), _geometry.getNormal() ) > 0 ? 1 : -1;
		int Flag2 = glm::dot( Point2 - _geometry.getPoint(), _geometry.getNormal() ) > 0 ? 1 : -1;

		if (Flag1 != Flag2) { return true; }


		return false;
	}
}