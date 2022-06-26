#include "CookTorranceBRDF.h"

namespace RT_ISICG
{
	float CookTorranceBRDF::compute_D( const Vec3f & h, const Vec3f & normal ) const
	{
		float alpha2 = _rugosite * _rugosite;

		return pow( alpha2, 2 )
			   / ( PIf * pow( ( pow( glm::dot( normal, h ), 2 ) * ( pow( alpha2, 2 ) - 1 ) + 1 ), 2 ) );
	}

	float CookTorranceBRDF::compute_G1( const float X, float K ) const { return X / ( X * ( 1.f - K ) + K ); }

	float CookTorranceBRDF::compute_G( const Vec3f & wo, const Vec3f & wi, const Vec3f & normal ) const
	{
		float K = ( _rugosite + 1.f ) * ( _rugosite + 1.f ) / 8.f;
		return this->compute_G1( glm::dot( normal, wo ), K ) * this->compute_G1( glm::dot( normal, wi ), K );
	}

	Vec3f CookTorranceBRDF::compute_F( const Vec3f & wo, const Vec3f & h ) const
	{
		float x = pow( ( 1.f - glm::dot( h, wo ) ), 5 );

		return _F0 + ( 1.f - _F0 ) * x;
	}

	Vec3f CookTorranceBRDF::evaluate( const Vec3f & p_wo, const Vec3f & p_wi, const Vec3f & p_normal ) const
	{
		Vec3f h = ( p_wo + p_wi ) / glm::length( p_wo + p_wi );
		float D = this->compute_D( h, p_normal );
		float G = this->compute_G( p_wo, p_wi, p_normal );
		Vec3f F = this->compute_F( p_wo, h );

		return ( D * F * G ) / ( 4.f * glm::dot( p_wo, p_normal ) * glm::dot( p_wi, p_normal ) );
	}
} // namespace RT_ISICG