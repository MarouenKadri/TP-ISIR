#pragma once
#include "DirectLightingIntegrator.h"

namespace RT_ISICG
{
	class WhittedIntegrator : public DirectLightingIntegrator
	{
	  public:
		WhittedIntegrator() : DirectLightingIntegrator() {}
		virtual ~WhittedIntegrator() = default;

		virtual Vec3f Li( const Scene & p_scene,
						  const Ray &	p_ray,
						  const float	p_tMin,
						  const float	p_tMax ) const override;

		const IntegratorType getType() const override { return IntegratorType::WHITTED; }

		virtual Vec3f trace( const Scene & p_scene,
							 const Ray &   p_ray,
							 const float   p_tMin,
							 const float   p_tMax,
							 const int	   p_bounces,
							 const bool	   inside ) const;

	  protected:
		int _nbBounces = 5;
	};
} // namespace RT_ISICG