#include "triangle_mesh_geometry.hpp"
#include "objects/triangle_mesh.hpp"

namespace RT_ISICG
{
	TriangleMeshGeometry::TriangleMeshGeometry( const unsigned int p_v0,
												const unsigned int p_v1,
												const unsigned int p_v2,
												MeshTriangle *	   p_refMesh )
		: _v0( p_v0 ), _v1( p_v1 ), _v2( p_v2 ), _refMesh( p_refMesh )
	{
		Vec3f v0	= _refMesh->_vertices[ p_v0 ];
		Vec3f v1	= _refMesh->_vertices[ p_v1 ];
		Vec3f v2	= _refMesh->_vertices[ p_v2 ];
		_faceNormal = glm::normalize( glm::cross( v1 - v0, v2 - v0 ) );

		_centroid = ( v0 + v1 + v2 ) / 3.f;

		_min.x = glm::min( glm::min( v0.x, v1.x ), v2.x );
		_min.y = glm::min( glm::min( v0.y, v1.y ), v2.y );
		_min.z = glm::min( glm::min( v0.z, v1.z ), v2.z );

		_max.x = glm::max( glm::max( v0.x, v1.x ), v2.x );
		_max.y = glm::max( glm::max( v0.y, v1.y ), v2.y );
		_max.z = glm::max( glm::max( v0.z, v1.z ), v2.z );
	}

	bool TriangleMeshGeometry::intersect( const Ray & p_ray, float & p_t ) const
	{
		const Vec3f & o	 = p_ray.getOrigin();
		const Vec3f & d	 = p_ray.getDirection();

		const Vec3f & v0 = _refMesh->_vertices[ _v0 ];
		const Vec3f & v1 = _refMesh->_vertices[ _v1 ];
		const Vec3f & v2 = _refMesh->_vertices[ _v2 ];

		const Vec3f n0 = _refMesh->_normals[ _v0 ];
		const Vec3f n1 = _refMesh->_normals[ _v1 ];
		const Vec3f n2 = _refMesh->_normals[ _v2 ];

		/// TODO
		Vec3f e1, e2, h, s, q;
		float a, f, u, v;

		e1 = v1 - v0;
		e2 = v2 - v0;
		h  = glm::cross(d, e2);
		a  = glm::dot(e1, h);
		if (a > -FLT_EPSILON && a < FLT_EPSILON) return false;

		f = 1.f / a;
		s = o - v0;
		u = f * glm::dot(s, h);
		if ( u < 0.f || u > 1.f ) return false;

		q = glm::cross(s, e1);
		v = f * glm::dot(d, q);
		if ( v < 0.f || u + v > 1.f ) return false;

		_faceNormal = (u * n1) + (v * n2) + (( 1.f - u - v ) * n0);

		p_t = f * glm::dot(e2, q);
		//return true;
		if ( p_t > FLT_EPSILON ) { return true; }
		return false;
	}

} // namespace RT_ISICG
