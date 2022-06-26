#ifndef __RT_ISICG_BRDF_PHONG__
#define __RT_ISICG_BRDF_PHONG__

#include "defines.hpp"

namespace RT_ISICG
{
	class PhongBRDF
	{
	  public:
		PhongBRDF( const Vec3f & p_ks, const float p_brillance ) : _ks( p_ks ), _brillance( p_brillance ) {};

		inline Vec3f evaluate( const Vec3f & p_wo, const Vec3f & p_wi, const Vec3f & p_normal ) const
		{
			Vec3f wr		= glm::reflect( p_wi, p_normal );
			float cos_alpha = glm::dot( p_wo, wr );
			return _ks * glm::pow( cos_alpha, float( _brillance ) );
		}

		inline const Vec3f & getKd() const { return _ks; }

		inline const float getBrillance() const { return _brillance; }

	  private:
		Vec3f _ks;
		int	  _brillance;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_PHONG__
