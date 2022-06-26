#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "scene.hpp"
#include "objects/triangle_mesh.hpp"

#include "materials/color_material.hpp"
#include "materials/lambert_material.hpp"
#include "materials/MatteMaterial.h"
#include "materials/PlasticMaterial.h"

#include "materials/MicrofacetMaterial.h"
#include "materials/BlinnPlasticMaterial.h"
#include "materials/MirrorMaterial.h"
#include "materials/TransparentMaterial.h"

#include "objects/sphere.hpp"
#include "objects/Plane.h"


#include "lights/PointLight.h"
#include "lights/QuadLight.h"

//#define DATA_PATH "../data/"

namespace RT_ISICG
{
	Scene::Scene() { _addMaterial( new ColorMaterial( "default", WHITE ) ); }

	Scene::~Scene()
	{
		for ( const ObjectMapPair & object : _objectMap )
		{
			delete object.second;
		}
		for ( const MaterialMapPair & material : _materialMap )
		{
			delete material.second;
		}
		for ( const BaseLight * light : _lightList )
		{
			delete light;
		}
	}

	void Scene::init()
	{
		std::string DATA_PATH = "data/";
		// =========================================================================
		// Add materials
		// =========================================================================   
		
		_addMaterial( new MatteMaterial( "WhiteMatte", WHITE, 0.6f ) );
		_addMaterial( new MatteMaterial( "YellowMatte", YELLOW, 0.6f ) );
		_addMaterial( new MatteMaterial( "RedMatte", RED, 0.6f ) );
		_addMaterial( new MatteMaterial( "GreenMatte", GREEN, 0.6f ) );
		_addMaterial( new MatteMaterial( "BlueMatte", BLUE, 0.6f ) );
		_addMaterial( new MatteMaterial( "GreyMatte", GREY, 0.6f ) );
		_addMaterial( new MatteMaterial( "MagentaMatte", MAGENTA, 0.6f ) );
		_addMaterial( new MatteMaterial( "CyanMatte", CYAN, 0.6f ) );

		_addMaterial( new MicrofacetMaterial( "gold", RED, 0.5f, 0.5f ) );
		_addMaterial( new TransparentMaterial( "transparent", 1.3f ) );
		_addMaterial( new MirrorMaterial( "mirror" ) );        

	














		// =========================================================================
		// Add objects
		// =========================================================================
	
		_addObject( new Sphere( "Sphere1", Vec3f( -2.f, -0.8f, 5.f ), 1.5f ) );
		_attachMaterialToObject( "transparent", "Sphere1" );

		_addObject( new Sphere( "Sphere2", Vec3f( 2.f, -0.8f, 5.f ), 1.5f ) );
		_attachMaterialToObject( "mirror", "Sphere2" );

	


		_addObject( new Sphere( "Sphere3", Vec3f( -1.f, -1.f, -1.f ), 0.25f ) );
		_attachMaterialToObject( "transparent", "Sphere3" );  

		    


		_addObject( new Sphere( "Sphere7", Vec3f( 0.f, -2.f, 3.f ), 1.f ) );
		_attachMaterialToObject( "gold", "Sphere7" );  

		
		_addObject( new Plane( "PlaneGround", Vec3f( 0.f, -4.5f, 0.f ), Vec3f( 0.f, -1.f, 0.f ) ) );
		_attachMaterialToObject( "mirror", "PlaneGround" );

		_addObject( new Plane( "PlaneLeft", Vec3f( 15.f, 0.f, 0.f ), Vec3f( -1.f, 0.f, 0.f ) ) );
		_attachMaterialToObject( "mirror", "PlaneLeft" );

		_addObject( new Plane( "PlaneCeiling", Vec3f( 0.f, 10.5f, 0.f ), Vec3f( 0.f, -1.f, 0.f ) ) );
		_attachMaterialToObject( "GreenMatte", "PlaneCeiling" );

		_addObject( new Plane( "PlaneRight", Vec3f( -15.f, 0.f, 0.f ), Vec3f( 1.f, 0.f, 0.f ) ) );
		_attachMaterialToObject( "mirror", "PlaneRight" );
		_addObject( new Plane( "PlaneFront", Vec3f( 0.f, 0.f, 22.5f ), Vec3f( 0.f, 0.f, -1.f ) ) );
		_attachMaterialToObject( "mirror", "PlaneFront" );
		
		
		// Add Lights
		_addLight( new PointLight( WHITE, 100.f, Vec3f( 0.f, 3.f, -5.f ) ) );
		_addLight( new PointLight( WHITE, 70.f, Vec3f( 5.f, 4.f, 4.f ) ) );
		_addLight( new PointLight( WHITE, 100.f, Vec3f( -10.f, 10.f, 33.f ) ) );

		_addLight(
			new QuadLight( Vec3f( -4.5f, 6.5f, 10.f ), Vec3f( -1.f, 0.f, 0.f ), Vec3f( 0.f, 1.f, 1.f ), BLUE, 70.f ) );
		_addLight(
			new QuadLight( Vec3f( 6.5f, 6.5f, 4.5f ), Vec3f( -1.f, 0.f, 0.f ), Vec3f( 0.f, 1.f, 1.f ), GREEN, 70.f ) );
		_addLight(
			new QuadLight( Vec3f( 4.f, 6.5f, 11.f ), Vec3f( -1.f, 0.f, 0.f ), Vec3f( 0.f, 1.f, 1.f ), RED, 70.f ) );
		_addLight(
			new QuadLight( Vec3f( -6.5f, 6.5f, 6.5f ), Vec3f( -1.f, 0.f, 0.f ), Vec3f( 0.f, 1.f, 1.f ), GREEN, 70.f ) );

		
		_addLight(
			new QuadLight( Vec3f( 2.f, 7.f, 5.f ), Vec3f( -4.f, 0.f, 0.f ), Vec3f( 0.f, 0.f, -4.f ), WHITE, 40.f ) );



	
		//loadFileTriangleMesh( "UVsphere", DATA_PATH + "uvsphere.obj" );
		//_attachMaterialToObject( "CyanMatte", "UVsphere_defaultobject" );
		//loadFileTriangleMesh( "UVbunny", DATA_PATH + "Bunny.obj" );
		//_attachMaterialToObject( "CyanMatte", "UVbunny_defaultobject" );
		//loadFileTriangleMesh( "UVconference", DATA_PATH + "conference/conference.obj" );
	
		
		
		

	
		

		

		




		     

	
	}

	void Scene::loadFileTriangleMesh( const std::string & p_name, const std::string & p_path )
	{
		std::cout << "Loading: " << p_path << std::endl;
		Assimp::Importer importer;

		// Read scene and triangulate meshes
		const aiScene * const scene
			= importer.ReadFile( p_path, aiProcess_Triangulate | aiProcess_GenNormals | aiProcess_GenUVCoords );

		if ( scene == nullptr ) { throw std::runtime_error( "Fail to load file: " + p_path ); }

		unsigned int cptTriangles = 0;
		unsigned int cptVertices  = 0;

		for ( unsigned int m = 0; m < scene->mNumMeshes; ++m )
		{
			const aiMesh * const mesh = scene->mMeshes[ m ];
			if ( mesh == nullptr ) { throw std::runtime_error( "Fail to load file: " + p_path + ": mesh is null" ); }

			const std::string meshName = p_name + "_" + std::string( mesh->mName.C_Str() );
			std::cout << "-- Load mesh " << m + 1 << "/" << scene->mNumMeshes << ": " << meshName << std::endl;

			cptTriangles += mesh->mNumFaces;
			cptVertices += mesh->mNumVertices;

			const bool hasUV = mesh->HasTextureCoords( 0 );

			MeshTriangle * triMesh = new MeshTriangle( meshName );
			// Vertices before faces otherwise face normals cannot be computed.
			for ( unsigned int v = 0; v < mesh->mNumVertices; ++v )
			{
				triMesh->addVertex( mesh->mVertices[ v ].x, mesh->mVertices[ v ].y, mesh->mVertices[ v ].z );
				triMesh->addNormal( mesh->mNormals[ v ].x, mesh->mNormals[ v ].y, mesh->mNormals[ v ].z );
				if ( hasUV ) triMesh->addUV( mesh->mTextureCoords[ 0 ][ v ].x, mesh->mTextureCoords[ 0 ][ v ].y );
			}
			for ( unsigned int f = 0; f < mesh->mNumFaces; ++f )
			{
				const aiFace & face = mesh->mFaces[ f ];
				triMesh->addTriangle( face.mIndices[ 0 ], face.mIndices[ 1 ], face.mIndices[ 2 ] );
			}

			triMesh->buildBVH();

	

			_addObject( triMesh );

			const aiMaterial * const mtl = scene->mMaterials[ mesh->mMaterialIndex ];
			if ( mtl == nullptr )
			{
				std::cerr << "Material undefined," << meshName << " assigned to default material" << std::endl;
			}
			else
			{
				Vec3f kd = WHITE;
				Vec3f ks = BLACK;
				float s	 = 0.f;

				aiColor3D aiKd;
				if ( mtl->Get( AI_MATKEY_COLOR_DIFFUSE, aiKd ) == AI_SUCCESS ) kd = Vec3f( aiKd.r, aiKd.g, aiKd.b );
				aiColor3D aiKs;
				if ( mtl->Get( AI_MATKEY_COLOR_SPECULAR, aiKs ) == AI_SUCCESS ) ks = Vec3f( aiKs.r, aiKs.g, aiKs.b );
				float aiS = 0.f;
				if ( mtl->Get( AI_MATKEY_SHININESS, aiS ) == AI_SUCCESS ) s = aiS;
				aiString mtlName;
				mtl->Get( AI_MATKEY_NAME, mtlName );

				//_addMaterial( new PlasticMaterial( std::string( mtlName.C_Str() ), kd, ks, int(s+0.5f) ) ); 
					
				_attachMaterialToObject( mtlName.C_Str(), meshName );
			}

			std::cout << "-- [DONE] " << triMesh->getNbTriangles() << " triangles, " << triMesh->getNbVertices()
					  << " vertices." << std::endl;
		}
		std::cout << "[DONE] " << scene->mNumMeshes << " meshes, " << cptTriangles << " triangles, " << cptVertices
				  << " vertices." << std::endl;
	}


	bool Scene::intersect( const Ray & p_ray, const float p_tMin, const float p_tMax, HitRecord & p_hitRecord ) const
	{
		float tMax = p_tMax;
		bool  hit  = false;
		for ( const ObjectMapPair & object : _objectMap )
		{
			if ( object.second->intersect( p_ray, p_tMin, tMax, p_hitRecord ) )
			{
				tMax = p_hitRecord._distance; // update tMax to conserve the nearest hit
				hit	 = true;
			}
		}
		return hit;
	}

	bool Scene::intersectAny(const Ray& p_ray, const float p_tMin, const float p_tMax) const 
	{
		for ( const ObjectMapPair & object : _objectMap )
		{
			if ( object.second->intersectAny( p_ray, p_tMin, p_tMax ) )
			{
				return true;
			}
		}
		return false;
	}

	void Scene::_addObject( BaseObject * p_object )
	{
		const std::string & name = p_object->getName();
		if ( _objectMap.find( name ) != _objectMap.end() )
		{
			std::cout << "[Scene::addObject] Object \'" << name << "\' already exists" << std::endl;
			delete p_object;
		}
		else
		{
			_objectMap[ name ] = p_object;
			_objectMap[ name ]->setMaterial( _materialMap[ "default" ] );
		}
	}

	void Scene::_addMaterial( BaseMaterial * p_material )
	{
		const std::string & name = p_material->getName();
		if ( _materialMap.find( name ) != _materialMap.end() )
		{
			std::cout << "[Scene::addMaterial] Material \'" << name << "\' already exists" << std::endl;
			delete p_material;
		}
		else
		{
			_materialMap[ name ] = p_material;
		}
	}

	void Scene::_addLight( BaseLight * p_light ) { _lightList.emplace_back( p_light ); }

	void Scene::_attachMaterialToObject( const std::string & p_materialName, const std::string & p_objectName )
	{
		if ( _objectMap.find( p_objectName ) == _objectMap.end() )
		{
			std::cout << "[Scene::attachMaterialToObject] Object \'" << p_objectName << "\' does not exist"
					  << std::endl;
		}
		else if ( _materialMap.find( p_materialName ) == _materialMap.end() )
		{
			std::cout << "[Scene::attachMaterialToObject] Material \'" << p_materialName << "\' does not exist, "
					  << "object \'" << p_objectName << "\' keeps its material \'"
					  << _objectMap[ p_objectName ]->getMaterial()->getName() << "\'" << std::endl;
		}
		else
		{
			_objectMap[ p_objectName ]->setMaterial( _materialMap[ p_materialName ] );
		}
	}

} // namespace RT_ISICG
