#ifndef __RT_ISICG_MICROFACET_MATERIAL__
#define __RT_ISICG_MICROFACET_MATERIAL__

#include "base_material.hpp"
#include "brdfs/CookTorranceBRDF.h"
#include "brdfs/OrenNayarBRDF.h"

namespace RT_ISICG
{
	class MicrofacetMaterial : public BaseMaterial
	{
	  public:
		MicrofacetMaterial( const std::string & p_name,
							const Vec3f &		p_color,
							const float			p_rugosite,
							const float			p_metalness )
			: BaseMaterial( p_name ), OrenNayarbrdf( p_color, p_rugosite ), CookTorrancebrdf( p_color, p_rugosite ),
			  _metalness( p_metalness )
		{
		}

		virtual ~MicrofacetMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			Vec3f diffuse
				= OrenNayarbrdf.evaluate( -p_ray.getDirection(), p_lightSample._direction, p_hitRecord._normal );
			Vec3f specular
				= CookTorrancebrdf.evaluate( -p_ray.getDirection(), p_lightSample._direction, p_hitRecord._normal );

			return ( 1.f - _metalness ) * diffuse + _metalness * specular;
		}

		inline const Vec3f & getFlatColor() const override { return OrenNayarbrdf.getKd(); }

	  protected:
		OrenNayarBRDF		   OrenNayarbrdf;
		CookTorranceBRDF CookTorrancebrdf;
		float				   _metalness;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_MICROFACET_MATERIAL__
