#include "aabb.hpp"

namespace RT_ISICG
{
	bool AABB::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		/// TODO
		Vec3f ro = p_ray.getOrigin();
		Vec3f rd = p_ray.getDirection();

		
		float diff_xmin = _min.x - ro.x;
	
		if (diff_xmin * rd.x > 0) 
		{
			float nbpas = diff_xmin / rd.x;
			if ( nbpas > p_tMin && nbpas < p_tMax )
			{
				float py = ro.y + ( rd.y * nbpas );
				float pz = ro.z + ( rd.z * nbpas );
				if ( py > _min.y && py < _max.y && pz > _min.z && pz < _max.z ) return true;
			}
		}

		float diff_xmax = _max.x - ro.x;
		if ( diff_xmax * rd.x > 0 )
		{
			float nbpas = diff_xmax / rd.x;
			if ( nbpas > p_tMin && nbpas < p_tMax )
			{
				float py = ro.y + ( rd.y * nbpas );
				float pz = ro.z + ( rd.z * nbpas );
				if ( py > _min.y && py < _max.y && pz > _min.z && pz < _max.z ) return true;
			}
		}

		
		float diff_ymin = _min.y - ro.y;
		if ( diff_ymin * rd.y > 0 )
		{
			float nbpas = diff_ymin / rd.y;
			if ( nbpas > p_tMin && nbpas < p_tMax )
			{
				float px = ro.x + ( rd.x * nbpas );
				float pz = ro.z + ( rd.z * nbpas );
				if ( px > _min.x && px < _max.x && pz > _min.z && pz < _max.z ) return true;
			}
		}

		
		float diff_ymax = _max.y - ro.y;
		if ( diff_ymax * rd.y > 0 )
		{
			float nbpas = diff_ymax / rd.y;
			if ( nbpas > p_tMin && nbpas < p_tMax )
			{
				float px = ro.x + ( rd.x * nbpas );
				float pz = ro.z + ( rd.z * nbpas );
				if ( px > _min.x && px < _max.x && pz > _min.z && pz < _max.z ) return true;
			}
		}

		
		float zmin = _min.z - ro.z;
		if ( zmin * rd.z > 0 )
		{
			float nbpas = zmin / rd.z;
			if ( nbpas > p_tMin && nbpas < p_tMax )
			{
				float px = ro.x + ( rd.x * nbpas );
				float py = ro.y + ( rd.y * nbpas );
				if ( px > _min.x && px < _max.x && py > _min.y && py < _max.y ) return true;
			}
		}

		
		float zmax = _max.z - ro.z;
		if ( zmax * rd.z > 0 )
		{
			float nbpas = zmax / rd.z;
			if ( nbpas > p_tMin && nbpas < p_tMax )
			{
				float px = ro.x + ( rd.x * nbpas );
				float py = ro.y + ( rd.y * nbpas );
				if ( px > _min.x && px < _max.x && py > _min.y && py < _max.y ) return true;
			}
		}


		return false;
	}
} // namespace RT_ISICG
