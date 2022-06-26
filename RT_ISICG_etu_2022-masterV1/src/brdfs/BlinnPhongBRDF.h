#ifndef __RT_ISICG_BRDF_BLINNPHONG__
#define __RT_ISICG_BRDF_BLINNPHONG__

#include "defines.hpp"

namespace RT_ISICG
{
	class BlinnPhongBRDF
	{
	  public:
		BlinnPhongBRDF( const Vec3f & p_ks, const float p_brillance ) : _ks( p_ks ), _brillance( p_brillance ) {};

		inline Vec3f evaluate( const Vec3f & p_wo, const Vec3f & p_wi, const Vec3f & p_normal ) const
		{
			Vec3f h			= ( p_wo + p_wi ) / glm::length( p_wo + p_wi );
	
			return _ks * glm::pow( glm::dot( h, p_normal ), float( _brillance ) );
		}

		inline const Vec3f & getKd() const { return _ks; }

		inline const float getBrillance() const { return _brillance; }

	  private:
		Vec3f _ks;
		int	  _brillance;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_BLINNPHONG__