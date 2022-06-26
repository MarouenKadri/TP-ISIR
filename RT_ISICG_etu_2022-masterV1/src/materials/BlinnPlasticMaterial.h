#ifndef __RT_ISICG_BLINNPLASTIC_MATERIAL__
#define __RT_ISICG_BLINNPLASTIC_MATERIAL__

#include "base_material.hpp"
#include "brdfs/BlinnPhongBRDF.h"
#include "brdfs/lambert_brdf.hpp"

namespace RT_ISICG
{
	class BlinnPlasticMaterial : public BaseMaterial
	{
	  public:
		BlinnPlasticMaterial( const std::string & p_name,
							  const Vec3f &		  p_color,
							  const int			  p_brillance,
							  const float		  p_ratio_metalness )
			: BaseMaterial( p_name ), Lambertbrdf( p_color ), BlinnPhongbrdf( p_color, p_brillance ),
			  _ratio_metalness( p_ratio_metalness )
		{
		}

		virtual ~BlinnPlasticMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			Vec3f diffuse = Lambertbrdf.evaluate();
			Vec3f specular
				= BlinnPhongbrdf.evaluate( -p_ray.getDirection(), p_lightSample._direction, p_hitRecord._normal );

			return ( 1.f - _ratio_metalness ) * diffuse + _ratio_metalness * specular;
		}

		inline const Vec3f & getFlatColor() const override { return Lambertbrdf.getKd(); }

	  protected:
		LambertBRDF	   Lambertbrdf;
		BlinnPhongBRDF BlinnPhongbrdf;
		float		   _ratio_metalness;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_BLINNPLASTIC_MATERIAL__