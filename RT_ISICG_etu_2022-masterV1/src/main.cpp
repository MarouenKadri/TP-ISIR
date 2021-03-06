#include "cameras/perspective_camera.hpp"
#include "defines.hpp"
#include "renderer.hpp"

namespace RT_ISICG
{
	int main( int argc, char ** argv )
	{
		const int imgWidth	= 600;
		const int imgHeight = 400;
		

		// Create a texture to render the scene.
		Texture img = Texture( imgWidth, imgHeight );

		// Create and init scene.
		Scene scene;
		scene.init();

		// Create a perspective camera.

		PerspectiveCamera camera( Vec3f( 0.f, 2.f, -6.f ),
								  Vec3f( 0.f, 0.f, 30.f ),
								  Vec3f( 0.f, 1.f, 0.f ),
								  60.f,
								  float( imgWidth ) / imgHeight );
		

		
		


		// Create and setup the renderer.
		Renderer renderer;

		renderer.setNbLightSamples( 1 );
		renderer.setNbPixelSamples( 16 );
	


		renderer.setIntegrator( IntegratorType::WHITTED
		);
		renderer.setBackgroundColor( GREY );
		
		

		// Launch rendering.
		std::cout << "Rendering..." << std::endl;
		std::cout << "- Image size: " << imgWidth << "x" << imgHeight << std::endl;

		float renderingTime = renderer.renderImage( scene, &camera, img );

		std::cout << "-> Done in " << renderingTime << "ms" << std::endl;

		// Save rendered image.
		const std::string imgName = "image.jpg";
		img.saveJPG( RESULTS_PATH + imgName );

		return EXIT_SUCCESS;
	}
} // namespace RT_ISICG

int main( int argc, char ** argv )
{
	try
	{
		return RT_ISICG::main( argc, argv );
	}
	catch ( const std::exception & e )
	{
		std::cerr << "Exception caught:" << std::endl << e.what() << std::endl;
	}
}
