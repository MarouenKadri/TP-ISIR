#ifndef __RT_ISICG_BRDF_ORENNAYAR__
#define __RT_ISICG_BRDF_ORENNAYAR__

#include "defines.hpp"

namespace RT_ISICG
{
	class OrenNayarBRDF
	{
	  public:
		OrenNayarBRDF( const Vec3f & p_kd, const float p_sigma ) : _kd( p_kd ), _sigma( p_sigma ) {};

		inline Vec3f evaluate( const Vec3f & p_do, const Vec3f & p_di, const Vec3f & p_normal ) const
		{
			// calcul des theta
			float cos_theta_i	  = glm::max( 0.f, glm::dot( p_normal, p_di ) );
			float cos_theta_r	  = glm::max( 0.f, glm::dot( p_normal, p_do ) );
			float theta_i		  = glm::acos( cos_theta_i );
			float theta_o		  = glm::acos( cos_theta_r );

			
			
			float Phi_i = glm::acos(glm::dot( glm::cross( p_normal, p_di ), glm::normalize( p_di - ( cos_theta_i * p_normal ) ) ) );
			float Phi_o = glm::acos(glm::dot( glm::cross( p_normal, p_di ), glm::normalize( p_do - ( cos_theta_r * p_normal ) ) ) );

			float alpha = glm::max( theta_i, theta_o );
			float beta	= glm::min( theta_i, theta_o );

			float sigma2 = _sigma * _sigma;
			float A		 = 1.f - 0.5f * ( sigma2 / ( sigma2 + 0.33f ) );
			float B		 = 0.45f * ( sigma2 / ( sigma2 + 0.09f ) );
			return _kd * INV_PIf * (A + ( B * glm::max( 0.f, glm::cos( Phi_i - Phi_o ) ) * glm::sin( alpha ) * glm::tan( beta )) );
		}

		inline const Vec3f & getKd() const { return _kd; }

	  private:
		Vec3f _kd = WHITE;
		float _sigma;  
		

	};
} // namespace RT_ISICG

#endif // __RT_ISICG_BRDF_LAMBERT__
