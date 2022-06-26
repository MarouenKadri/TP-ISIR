#include "DirectLightingIntegrator.h"

namespace RT_ISICG
{
	Vec3f DirectLightingIntegrator::Li( const Scene & p_scene,
										const Ray &	  p_ray,
										const float	  p_tMin,
										const float	  p_tMax ) const
	{
		HitRecord ht;
		if ( p_scene.intersect( p_ray, p_tMin, p_tMax, ht ) )
		{
			return this->_directLighting( p_scene, p_ray, ht, p_tMax );
		}
		else
		{
			return _backgroundColor;
		}
	}

	Vec3f DirectLightingIntegrator::_directLighting( const Scene &	   p_scene,
													 const Ray &	   p_ray,
													 const HitRecord & ht,
													 const float	   p_tMax ) const
	{
		Vec3f	  finalColor = Vec3f( 0 ), li;
		LightList llist		 = p_scene.getLights();

		for ( int i = 0; i < llist.size(); i++ )
		{
			li = Vec3f( 0 );
			for ( int x = 0; x < _nbLightSamples; x++ )
			{
				LightSample ls			= llist[ i ]->sample( ht._point );
				Vec3f		objectColor = llist[ i ]->getFlatColor();

				Ray shadow_ray = Ray( ht._point, ls._direction );
				shadow_ray.offset( ht._normal );
				float cos_theta = glm::max( 0.f, glm::dot( ht._normal, ls._direction ) );
				Vec3f mtl
					= ht._object->getMaterial()->shade( p_ray, ht, ls ) * ( objectColor * ls._radiance * cos_theta );

				if ( !p_scene.intersectAny( shadow_ray, SHADOW_EPSILON, ls._distance ) )
					return li += mtl + ( ht._distance / p_tMax ) * Vec3f( 1.f );
				else
					return ( li += mtl + ( ht._distance / p_tMax ) * Vec3f( 1.f ) );
			}
			if ( llist[ i ]->getSurface() )
			{
				li /= float( _nbLightSamples );
				finalColor += li;
			}
			else
			{
				finalColor += li;
			}
		}

		finalColor /= float( llist.size() );
		return finalColor;
	}

} // namespace RT_ISICG