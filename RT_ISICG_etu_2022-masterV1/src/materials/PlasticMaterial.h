#ifndef __RT_ISICG_PLASTIC_MATERIAL__
#define __RT_ISICG_PLASTIC_MATERIAL__

#include "base_material.hpp"
#include "brdfs/PhongBRDF.h"
#include "brdfs/lambert_brdf.hpp"

namespace RT_ISICG
{
	class PlasticMaterial : public BaseMaterial
	{
	  public:
		PlasticMaterial( const std::string & p_name,
						 const Vec3f &		 p_color,
						 const int			 p_brillance,
						 const float		 p_ratio_metalness )
			: BaseMaterial( p_name ), _lambert_brdf( p_color ), _phong_brdf( p_color, p_brillance ),
			  _ratio_metalness( p_ratio_metalness )
		{
		}

		virtual ~PlasticMaterial() = default;

		Vec3f shade( const Ray &		 p_ray,
					 const HitRecord &	 p_hitRecord,
					 const LightSample & p_lightSample ) const override
		{
			Vec3f diffuse_color = _lambert_brdf.evaluate();
			Vec3f specular_color
				= _phong_brdf.evaluate( -p_ray.getDirection(), p_lightSample._direction, p_hitRecord._normal );

			return ( 1.f - _ratio_metalness ) * diffuse_color + _ratio_metalness * specular_color;
		}

		inline const Vec3f & getFlatColor() const override { return _lambert_brdf.getKd(); }

	  protected:
		LambertBRDF _lambert_brdf;
		PhongBRDF	_phong_brdf;
		float		_ratio_metalness;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_PLASTIC_MATERIAL__
