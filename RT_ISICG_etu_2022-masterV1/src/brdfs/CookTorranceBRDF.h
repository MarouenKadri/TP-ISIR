#pragma once
#ifndef __RT_ISICG_BRDF_CookTorrance__
#define __RT_ISICG_BRDF_CookTorrance__
#include "defines.hpp"
namespace RT_ISICG
{
	class CookTorranceBRDF
	{
	  public:
		CookTorranceBRDF( const Vec3f & p_F0, const float p_rugosite ) : _F0( p_F0 ), _rugosite( p_rugosite ) {};

		virtual float compute_D( const Vec3f & h, const Vec3f & normal ) const;

		virtual float compute_G1( const float x, float k ) const;
		virtual float compute_G( const Vec3f & wo, const Vec3f & wi, const Vec3f & normal ) const;

		virtual Vec3f compute_F( const Vec3f & wo, const Vec3f & h ) const;

		virtual Vec3f evaluate( const Vec3f & p_wo, const Vec3f & p_wi, const Vec3f & p_normal ) const;

		inline const Vec3f & getF0() const { return _F0; }

	  private:
		Vec3f _F0;
		float _rugosite;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_CookTorrance__