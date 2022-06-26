#include <algorithm>

#include "bvh.hpp"
#include "geometry/triangle_mesh_geometry.hpp"
#include "utils/chrono.hpp"

namespace RT_ISICG
{
	void BVH::build( std::vector<TriangleMeshGeometry> * p_triangles )
	{
		std::cout << "Building BVH..." << std::endl;
		if ( p_triangles == nullptr || p_triangles->empty() )
		{
			throw std::exception( "BVH::build() error: no triangle provided" );
		}
		_triangles = p_triangles;

		Chrono chr;
		chr.start();

		/// TODO
		_root = new BVHNode();
		_buildRec( _root, 0, _triangles->size(), 0);

		chr.stop();

		std::cout << "[DONE]: " << chr.elapsedTime() << "s" << std::endl;
	}

	bool BVH::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const
	{
		if ( !_root->_aabb.intersect( p_ray, p_tMin, p_tMax ) ) return false;
		return _intersectRec( _root, p_ray, p_tMin, p_tMax, p_hitRecord );
	}

	bool BVH::intersectAny( const Ray & p_ray, const float p_tMin, const float p_tMax ) const
	{
		if ( !_root->_aabb.intersect( p_ray, p_tMin, p_tMax ) ) return false;
		return _intersectAnyRec( _root, p_ray, p_tMin, p_tMax );
	}

	void BVH::_buildRec( BVHNode *			p_node,
						 const unsigned int p_firstTriangleId,
						 const unsigned int p_lastTriangleId,
						 const unsigned int p_depth )
	{
		
		for (int i = p_firstTriangleId; i < p_lastTriangleId; i++) {
			p_node->_aabb.extend( _triangles->at( i ).getVecMin() );
			p_node->_aabb.extend( _triangles->at( i ).getVecMax() );
		}

		p_node->_firstTriangleId	= p_firstTriangleId;
		p_node->_lastTriangleId		= p_lastTriangleId;
		p_node->_left				= nullptr;
		p_node->_right				= nullptr;

	
		if ( p_depth < _maxDepth && p_lastTriangleId - p_firstTriangleId > _maxTrianglesPerLeaf ) 
		{
			
			Vec3f ctmp			= _triangles->at( p_firstTriangleId ).getCentroid();
			AABB  aabb_centroid = AABB( ctmp, ctmp );
			for ( int i = p_firstTriangleId; i < p_lastTriangleId; i++ )
				aabb_centroid.extend( _triangles->at( i ).getCentroid() );

			Vec3f aabb_c_min  = aabb_centroid.getMin(), aabb_c_max = aabb_centroid.getMax();
			float dx		  = aabb_c_max.x - aabb_c_min.x;
			float dy		  = aabb_c_max.y - aabb_c_min.y;
			float dz		  = aabb_c_max.z - aabb_c_min.z;
			char  biggest_axe = dx > dy ? ( dx > dz ? 'X' : 'Z' ) : ( dy > dz ? 'Y' : 'Z' );

			
			float midpoint;
			if ( biggest_axe == 'X' )
				midpoint = ( aabb_c_max.x + aabb_c_min.x ) / 2.f; 
			else if ( biggest_axe == 'Y' )
				midpoint = ( aabb_c_max.y + aabb_c_min.y ) / 2.f;
			else
				midpoint = ( aabb_c_max.z + aabb_c_min.z ) / 2.f;

			
			int idPartition = _createPartition( biggest_axe, midpoint, p_firstTriangleId, p_lastTriangleId );
			

			p_node->_left = new BVHNode();
			p_node->_right = new BVHNode();
			_buildRec( p_node->_left, p_firstTriangleId, idPartition, p_depth + 1 );
			_buildRec( p_node->_right, idPartition, p_lastTriangleId, p_depth + 1 );
		}
		else
		{
			p_node->_left = nullptr;
			p_node->_right = nullptr;
		}
	}

	const unsigned int BVH::_createPartition(	char			   axe,
												float			   millieu,
												const unsigned int p_firstTriangleId,
												const unsigned int p_lastTriangleId ) 
	{

		if ( axe == 'X' )
		{
			midPointX cmp = { millieu };
			std::sort( std::next( _triangles->begin(), p_firstTriangleId ),
					   std::next( _triangles->begin(), p_lastTriangleId ),
					   cmp );

			for ( int i = p_firstTriangleId; i < p_lastTriangleId; i++ )
				if ( _triangles->at( i ).getCentroid().x >= millieu )  return i; 
		}
		else if ( axe == 'Y' )
		{
			midpointY cmp = { millieu };
			std::sort( std::next( _triangles->begin(), p_firstTriangleId ),
					   std::next( _triangles->begin(), p_lastTriangleId ),
					   cmp );

			for ( int i = p_firstTriangleId; i < p_lastTriangleId; i++ )
				if ( _triangles->at( i ).getCentroid().y >= millieu )  return i; 
		}
		else
		{
			midpointz cmp = { millieu };
			std::sort( std::next( _triangles->begin(), p_firstTriangleId ),
					   std::next( _triangles->begin(), p_lastTriangleId ),
					   cmp );

			for ( int i = p_firstTriangleId; i < p_lastTriangleId; i++ )
				if ( _triangles->at( i ).getCentroid().z >= millieu )  return i; 
		}

		
		
		return -5;
	}



	bool BVH::_intersectRec( const BVHNode * p_node,
							 const Ray &	 p_ray,
							 const float	 p_tMin,
							 const float	 p_tMax,
							 HitRecord &	 p_hitRecord ) const
	{
		/// TODO
		if ( p_node->isLeaf() ) 
		{ 
			//printf( "LEAF !!!!!\n" );
			float t, tmin = p_tMax + 1;
			int	  id_min = -1;

			for (int i = p_node->_firstTriangleId; i < p_node->_lastTriangleId; i++) 
				if ( _triangles->at( i ).intersect(p_ray, t) ) 
					if ( t <= p_tMax && t >= p_tMin && t < tmin )
					{
						tmin	= t;
						id_min	= i;
					}

			if ( id_min > 0 )
			{
				p_hitRecord._point	= p_ray.pointAtT( tmin );
				p_hitRecord._normal = _triangles->at( id_min ).getFaceNormal();
				p_hitRecord.faceNormal( p_ray.getDirection() );
				p_hitRecord._distance = tmin;
				p_hitRecord._object	  = nullptr;

				return true;
			}
			return false;
		}
		else 
		{
			HitRecord ht_left, ht_right;
			bool left_intersection = false, right_intersection = false;
			
			if ( p_node->_left->_aabb.intersect( p_ray, p_tMin, p_tMax ) )
			{
				 left_intersection = _intersectRec( p_node->_left, p_ray, p_tMin, p_tMax, ht_left );
			}

			if ( p_node->_right->_aabb.intersect( p_ray, p_tMin, p_tMax ) )
			{
				right_intersection = _intersectRec( p_node->_right, p_ray, p_tMin, p_tMax, ht_right );
			}


			if (left_intersection && right_intersection) 
			{
				if ( ht_left._distance < ht_right._distance )
				{
					_copyHitRecord( p_hitRecord, ht_left, p_ray.getDirection() );
				}
				else 
				{
					_copyHitRecord( p_hitRecord, ht_right, p_ray.getDirection() );
				}
					
				return true;
			}
			else if ( left_intersection )
			{
				_copyHitRecord( p_hitRecord, ht_left, p_ray.getDirection() );
				return true;
			}
			else if ( right_intersection )
			{
				_copyHitRecord( p_hitRecord, ht_right, p_ray.getDirection() );
				return true;
			}

			return false;
		}
	}



	bool BVH::_intersectAnyRec( const BVHNode * p_node,
								const Ray &		p_ray,
								const float		p_tMin,
								const float		p_tMax ) const
	{
		if ( p_node->isLeaf() )
		{
			float t = -1;
			for ( int i = p_node->_firstTriangleId; i < p_node->_lastTriangleId; i++ )
				if ( _triangles->at( i ).intersect( p_ray, t ) )
					if ( t <= p_tMax && t >= p_tMin ) return true;
			return false;
		}
		else
		{
			bool left_intersection = false;
			if ( p_node->_left->_aabb.intersect( p_ray, p_tMin, p_tMax ) )
				left_intersection = _intersectAnyRec( p_node->_left, p_ray, p_tMin, p_tMax );
			if ( left_intersection ) return true;

			if ( p_node->_right->_aabb.intersect( p_ray, p_tMin, p_tMax ) )
				return _intersectAnyRec( p_node->_right, p_ray, p_tMin, p_tMax );
			return false;
		}
	}

	void BVH::_copyHitRecord( HitRecord & ht_dest, HitRecord & ht_src, const Vec3f & ray_direction ) const
	{
		ht_dest._point	= ht_src._point;
		ht_dest._normal = ht_src._normal;
		ht_dest.faceNormal( ray_direction );
		ht_dest._distance = ht_src._distance;
		ht_dest._object	  = ht_src._object;
	}

} // namespace RT_ISICG
//