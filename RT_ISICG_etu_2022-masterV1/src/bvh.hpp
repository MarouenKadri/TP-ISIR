#ifndef __RT_ISICG_BVH__
#define __RT_ISICG_BVH__

#include "aabb.hpp"
#include "geometry/triangle_mesh_geometry.hpp"
#include "hit_record.hpp"
#include <vector>

namespace RT_ISICG
{
	class TriangleMeshGeometry;

	
	struct midPointX
	{
		float millieu;
		bool  operator()( TriangleMeshGeometry t1, TriangleMeshGeometry t2 ) const
		{
			
			return t1.getCentroid().x < t2.getCentroid().x;
		}
	};

	struct midpointY
	{
		float millieu;
		bool  operator()( TriangleMeshGeometry t1, TriangleMeshGeometry t2 ) const
		{
			
			return t1.getCentroid().y < t2.getCentroid().y;
		}
	};

	struct midpointz
	{
		float millieu;
		bool  operator()( TriangleMeshGeometry t1, TriangleMeshGeometry t2 ) const
		{
			
			return t1.getCentroid().z < t2.getCentroid().z;
		}
	};

	struct BVHNode
	{
		BVHNode() = default;
		~BVHNode()
		{
			delete _left;
			delete _right;
		}
		bool isLeaf() const { return ( _left == nullptr && _right == nullptr ); }

		AABB		 _aabb;
		BVHNode *	 _left			  = nullptr;
		BVHNode *	 _right			  = nullptr;
		unsigned int _firstTriangleId = 0;
		unsigned int _lastTriangleId  = 0;
	};

	class BVH
	{
	  public:
		BVH() = default;

		~BVH() { delete _root; }

		// Build the BVH from a list of triangles (call _buildRec).
		void build( std::vector<TriangleMeshGeometry> * p_triangles );

		// Search for the nearest intersection with the ray (call _intersectRec).
		bool intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const;
		// Search for the any intersection with the ray (call _intersectRec).
		bool intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const;

	

	  private:
		void _buildRec( BVHNode *		   p_node,
						const unsigned int p_firstTriangleId,
						const unsigned int p_nbTriangles,
						const unsigned int p_depth );

		const unsigned int _createPartition( char				axe,
											 float				millieu,
											 const unsigned int p_firstTriangleId,
											 const unsigned int p_lastTriangleId );

		bool _intersectRec( const BVHNode * p_node,
							const Ray &		p_ray,
							const float		p_tMin,
							const float		p_tMax,
							HitRecord &		p_hitRecord ) const;

		bool _intersectAnyRec( const BVHNode * p_node,
							   const Ray &	   p_ray,
							   const float	   p_tMin,
							   const float	   p_tMax ) const;

		// Copy correctly the hitRecord of the source to the destination hitRecord with the help of the ray direction
		void _copyHitRecord( HitRecord & ht_dest, HitRecord & ht_src, const Vec3f & ray_direction ) const;

	  private:
		std::vector<TriangleMeshGeometry> * _triangles = nullptr;
		BVHNode *							_root	   = nullptr;

		const unsigned int _maxTrianglesPerLeaf = 8;
		const unsigned int _maxDepth			= 32;
	};

} // namespace RT_ISICG

#endif // __RT_ISICG_BVH__