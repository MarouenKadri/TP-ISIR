#include "perspective_camera.hpp"
#include <glm/gtx/string_cast.hpp>

namespace RT_ISICG
{
	PerspectiveCamera::PerspectiveCamera( const float p_aspectRatio ) : _aspectRatio( p_aspectRatio )
	{
		_updateViewport();
	}

	PerspectiveCamera::PerspectiveCamera( const Vec3f & p_position,
										  const Vec3f & p_lookAt,
										  const Vec3f & p_up,
										  const float	p_fovy,
										  const float	p_aspectRatio )
		: BaseCamera( p_position ), _fovy( p_fovy ), _aspectRatio( p_aspectRatio )
	{
		_w = normalize( p_position - p_lookAt );
		_u = normalize( cross( p_up, _w ) );
		_v = cross( _w, _u );

		_updateViewport();
	}

	void PerspectiveCamera::_updateViewport()
	{
		_viewportV			   = _v * 2.0f * tan( glm::radians( _fovy * 0.5f ) ) * _focalDistance;
		_viewportU			   = _u * 2.0f * tan( glm ::radians( _fovy * 0.5f ) ) * _focalDistance * _aspectRatio;
		_viewportTopLeftCorner = -_w * _focalDistance + _position + _viewportV * 0.5f - _viewportU * 0.5f;
	}

} // namespace RT_ISICG