#ifndef __RT_ISICG_TRIANGLE_GEOMETRY__
#define __RT_ISICG_TRIANGLE_GEOMETRY__

#include "base_geometry.hpp"

namespace RT_ISICG
{
	class MeshTriangle;

	class TriangleMeshGeometry : public BaseGeometry
	{
	  public:
		TriangleMeshGeometry()			= delete;
		virtual ~TriangleMeshGeometry() = default;

		TriangleMeshGeometry( const unsigned int p_v0,
							  const unsigned int p_v1,
							  const unsigned int p_v2,
							  MeshTriangle *	 p_refMesh );

		bool intersect( const Ray & p_ray, float & p_t ) const;

		inline const Vec3f & getFaceNormal() const { return _faceNormal; }

		inline const Vec3f & getVecMin() const { return _min; }
		inline const Vec3f & getVecMax() const { return _max; }
		inline const Vec3f & getCentroid() const { return _max; }

	  private:
		MeshTriangle * _refMesh;
		union
		{
			struct
			{
				unsigned int _v0, _v1, _v2;
			};
			unsigned int _v[ 3 ] = { 0, 0, 0 };
		};

		mutable Vec3f _faceNormal;
		Vec3f		  _min, _max, _centroid;
	};
} // namespace RT_ISICG

#endif // __RT_ISICG_TRIANGLE_GEOMETRY__
