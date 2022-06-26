#ifndef __RT_ISICG_RENDERER__
#define __RT_ISICG_RENDERER__

#include "cameras/base_camera.hpp"
#include "cameras/perspective_camera.hpp"
#include "defines.hpp"
#include "integrators/base_integrator.h"
#include "texture.hpp"
#include "utils/chrono.hpp"

namespace RT_ISICG
{
	class Renderer
	{
	  public:
		Renderer();
		~Renderer() { delete _integrator; }

		void setIntegrator( const IntegratorType p_integratorType );
		void setBackgroundColor( const Vec3f & p_color );
		inline void setNbPixelSamples( const int p_nbPixelSamples ) { _nbPixelSamples = p_nbPixelSamples; }
		inline void setNbLightSamples( const int p_nbLightSamples ) { _nbLightSamples = p_nbLightSamples; }

		float renderImage( const Scene & p_scene, const BaseCamera * p_camera, Texture & p_texture );

	

	

	
	  private:
		BaseIntegrator * _integrator	 = nullptr;
		int				 _nbPixelSamples = 1;
		int				 _nbLightSamples = 1;
		int				 _nbBounces = 5;
		float			 _ratioArtificialGI = 0.f;
		
		// Monte-Carlo settings:
		int _nbEchantillon = 100;
		int _bounceMin	   = 5;
		int _bounceMax	   = 10; 
		float _render_distance = 100.f;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_RENDERER__
