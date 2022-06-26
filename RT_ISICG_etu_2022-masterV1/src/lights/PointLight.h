#pragma once
#include "base_light.hpp"

namespace RT_ISICG
{
	class PointLight : public BaseLight
	{
	  public:
		PointLight()		  = delete;
		virtual ~PointLight() = default;

		PointLight( const Vec3f & p_color, const float p_power, const Vec3f & p_pos )
			: BaseLight( p_color, p_power, false ), _position( p_pos )
		{
		}

		virtual LightSample sample( const Vec3f & p_point ) const override;

	  private:
		Vec3f _position;
	};
} // namespace RT_ISICG

