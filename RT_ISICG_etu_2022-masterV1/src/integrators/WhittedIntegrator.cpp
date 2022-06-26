#include "WhittedIntegrator.h"

namespace RT_ISICG
{
	Vec3f WhittedIntegrator::Li( const Scene & p_scene,
								 const Ray &   p_ray,
								 const float   p_tMin,
								 const float   p_tMax ) const
	{
		return trace( p_scene, p_ray, p_tMin, p_tMax, _nbBounces, false );
	}

	Vec3f WhittedIntegrator::trace( const Scene & p_scene,
									const Ray &	  p_ray,
									const float	  p_tMin,
									const float	  p_tMax,
									const int	  p_bounces,
									const bool	  inside ) const
	{
		HitRecord hitRecord;
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, hitRecord ) )
		{
			if ( p_bounces == 0 ) { return _directLighting( p_scene, p_ray, hitRecord, p_tMax ); }

			if ( hitRecord._object->getMaterial()->isMirror() )
			{
				Ray reflectRay = Ray( hitRecord._point, glm::reflect( p_ray.getDirection(), hitRecord._normal ) );
				reflectRay.offset( hitRecord._normal );
				return trace( p_scene, reflectRay, 0, p_tMax, p_bounces - 1, inside );
			}
			else if ( hitRecord._object->getMaterial()->isTransparent() )
			{
				float n1 = 1.f;
				float n2 = hitRecord._object->getMaterial()->getIOR();
				if ( inside )
				{
					n1 = hitRecord._object->getMaterial()->getIOR();
					n2 = 1.f;
				}

				Ray reflexion_ray = Ray( hitRecord._point, glm::reflect( p_ray.getDirection(), hitRecord._normal ) );
				reflexion_ray.offset( hitRecord._normal );
				Vec3f reflectLi = trace( p_scene, reflexion_ray, 0, p_tMax, p_bounces - 1, inside );

				float kr	= 1;
				float coeff = n1 / n2;

				float cosTheta_i = glm::dot( p_ray.getDirection(), hitRecord._normal );
				float sinTheta_i = glm::sqrt( 1.f - pow( cosTheta_i, 2 ) );
				float cosTheta_t = glm::sqrt( 1.f - pow( coeff * sinTheta_i, 2 ) );

				float rs = pow( ( n1 * cosTheta_i - n2 * cosTheta_t ) / ( n1 * cosTheta_i + n2 * cosTheta_t ), 2 );
				float rp = pow( ( n1 * cosTheta_t - n2 * cosTheta_i ) / ( n1 * cosTheta_t + n2 * cosTheta_i ), 2 );

				kr = ( rs + rp ) * 0.5f;

				if ( kr < 1.f )
				{
					Vec3f refractRay = glm::refract( p_ray.getDirection(), hitRecord._normal, coeff );

					Ray ray_refraction = Ray( hitRecord._point, refractRay );
					ray_refraction.offset( -hitRecord._normal );
					Vec3f refractLi = trace( p_scene, ray_refraction, 0, p_tMax, p_bounces - 1, !inside );

					return kr * reflectLi + ( 1.f - kr ) * refractLi;
				}
				else
				{
					return reflectLi;
				}
			}
			else
			{
				return _directLighting( p_scene, p_ray, hitRecord, p_tMax );
			}
		}
		else
		{
			return _backgroundColor;
		}
	}

} // namespace RT_ISICG