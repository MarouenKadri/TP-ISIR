#include "renderer.hpp"

#include "integrators/ray_cast_integrator.h"
#include "integrators/DirectLightingIntegrator.h"
#include "integrators/WhittedIntegrator.h"  

#include "utils/console_progress_bar.hpp"
#include "utils/random.hpp"

namespace RT_ISICG
{
	Renderer::Renderer() { _integrator = new RayCastIntegrator(); }

	void Renderer::setIntegrator( const IntegratorType p_integratorType )
	{
		if ( _integrator != nullptr ) { delete _integrator; }

		switch ( p_integratorType )
		{
			case IntegratorType::DIRECT_LIGHT:
			{
				_integrator = new DirectLightingIntegrator(  );
				break;
			}
			case IntegratorType::WHITTED:
			{
				_integrator = new WhittedIntegrator( );
				break;
			} 
		
			
			case IntegratorType::RAY_CAST:
			default:
			{
				_integrator = new RayCastIntegrator();
				break;
			}
		}
	}

	void Renderer::setBackgroundColor( const Vec3f & p_color )
	{
		if ( _integrator == nullptr ) { std::cout << "[Renderer::setBackgroundColor] Integrator is null" << std::endl; }
		else
		{
			_integrator->setBackgroundColor( p_color );
		}
	}

	float Renderer::renderImage( const Scene & p_scene, const BaseCamera * p_camera, Texture & p_texture )
	{
		const int width	 = p_texture.getWidth();
		const int height = p_texture.getHeight();

		Chrono			   chrono;
		ConsoleProgressBar progressBar;

		progressBar.start( height, 50 );
		chrono.start();

		#pragma omp parallel for
		for ( int j = 0; j < height; j++ )
		{
			for ( int i = 0; i < width; i++ )
			{
				Vec3f color = VEC3F_ZERO;
				auto  r		= double( i ) / ( width - 1 );
				auto  g		= double( j ) / ( height - 1 );
				auto  b		= 0;
				for ( int x = 0; x < _nbPixelSamples; x++ )
				{
					Ray ray = p_camera->generateRay( ( i + randomFloat() ) / ( width - 1.f ),
													 ( j + randomFloat() ) / ( height - 1.f ) );
					color += _integrator->Li( p_scene, ray, 0, 1000 );
				}
				// p_texture.setPixel( i, j, ( color / (float)_nbPixelSamples ) );
				p_texture.setPixel(
					i, j, glm::clamp( color / float( _nbPixelSamples ), VEC3F_ZERO, Vec3f( 1, 1, 1 ) ) );
			}
			progressBar.next();
		}

		chrono.stop();
		progressBar.stop();

		return chrono.elapsedTime();

}
} // namespace RT_ISICG
