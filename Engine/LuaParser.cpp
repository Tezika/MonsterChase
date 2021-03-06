#include "stdafx.h"
#include "LuaParser.h"
#include "GameObject.h"
#include "SubSystemHeaders.h"
#include "Assert.h"
#include "CommonUtility.h"

#include "ConsolePrint.h"
#include "Point2D.h"
#include "AABB.h"
#include <LuaWinLibs/lua.hpp>
#include <ReferenceCounting/SmartPtr.h>

#define lua_pop_top(L) lua_pop(L,1);

namespace Engine
{
	template<typename T, typename = typename std::enable_if<std::is_arithmetic<T>::value, T>::type>
	Point2D<T> ParsePointFromLua( lua_State* pLuaState )
	{
		assert( pLuaState );
		T x = 0;
		T y = 0;
		// Push the first key in;
		lua_pushnil( pLuaState );
		while (lua_next( pLuaState, -2 ) != 0)
		{
			assert( lua_type( pLuaState, -1 ) == LUA_TNUMBER );
			assert( lua_type( pLuaState, -2 ) == LUA_TSTRING );

			lua_Number value = lua_tonumber( pLuaState, -1 );
			const char* key = lua_tostring( pLuaState, -2 );
			if (strcmp( key, "x" ) == 0)
			{
				x = static_cast<T>(value);
			}
			else if (strcmp( key, "y" ) == 0)
			{
				y = static_cast<T>(value);
			}
			// pop the value
			lua_pop_top( pLuaState );
		}
		return Point2D<T>( x, y );
	}

	SmartPtr<GameObject> CreateGameObjectByFile( const char* i_fileName )
	{
		assert( i_fileName );
		size_t sizeOfFile = 0;
		void* pFileContents = Engine::LoadFile( i_fileName, sizeOfFile );
		SmartPtr<GameObject> ret;
		if (pFileContents && sizeOfFile)
		{
			// Create a new lua state
			lua_State* pLuaState = luaL_newstate();
			assert( pLuaState );

			luaL_openlibs( pLuaState );

			int result = 0;

			// Necessary stuff to process our data
			result = luaL_loadbuffer( pLuaState, reinterpret_cast<char*>(pFileContents), sizeOfFile, nullptr );
			assert( result == 0 );

			result = lua_pcall( pLuaState, 0, 0, 0 );
			assert( result == 0 );

			// Get the go table from the lua file
			result = lua_getglobal( pLuaState, "gameObject" );
			assert( result == LUA_TTABLE );

			// Retrieve the go's name
			lua_pushstring( pLuaState, "name" );
			result = lua_gettable( pLuaState, -2 );
			assert( result == LUA_TSTRING );
			const char* pName = lua_tostring( pLuaState, -1 );
			lua_pop_top( pLuaState );

			DEBUG_PRINT_GAMEPLAY( "-----------Start print out the GameObject info for '%s'-------------------", pName );

			// Retrieve the go's inital position
			lua_pushstring( pLuaState, "initial_position" );
			result = lua_gettable( pLuaState, -2 );
			assert( result == LUA_TTABLE );

			Point2D<float> initial_position = ParsePointFromLua<float>( pLuaState );
			lua_pop_top( pLuaState );
			DEBUG_PRINT_GAMEPLAY( "The initial position for the gameobject is %.3f, %.3f", initial_position.m_x, initial_position.m_y );

			// Retrieve the go's inital veclocity
			lua_pushstring( pLuaState, "initial_velocity" );
			result = lua_gettable( pLuaState, -2 );
			assert( result == LUA_TTABLE );

			Point2D<float> initial_velocity = ParsePointFromLua<float>( pLuaState );
			lua_pop_top( pLuaState );
			DEBUG_PRINT_GAMEPLAY( "The initial velocity for the gameobject is %.3f, %.3f", initial_velocity.m_x, initial_velocity.m_y );

			// ------- Physics -----------
			// Retrieve the go's physics settings
			lua_pushstring( pLuaState, "physics_settings" );
			result = lua_gettable( pLuaState, -2 );
			assert( result == LUA_TTABLE );

			// Retrieve the Mass 
			lua_pushstring( pLuaState, "mass" );
			result = lua_gettable( pLuaState, -2 );
			assert( result == LUA_TNUMBER );
			float mass = static_cast<float>(lua_tonumber( pLuaState, -1 ));
			DEBUG_PRINT_GAMEPLAY( "The mass for the gameobject is %.3f", mass );
			// Pop for mass
			lua_pop_top( pLuaState );

			// Retrieve the force
			lua_pushstring( pLuaState, "force" );
			result = lua_gettable( pLuaState, -2 );
			assert( result == LUA_TTABLE );
			Point2D<float> force = ParsePointFromLua<float>( pLuaState );
			DEBUG_PRINT_GAMEPLAY( "The force for the gameobject is %.3f, %.3f", force.m_x, force.m_y );
			// Pop for force
			lua_pop_top( pLuaState );

			// Retrieve the dragness
			lua_pushstring( pLuaState, "dragness" );
			result = lua_gettable( pLuaState, -2 );
			assert( result == LUA_TNUMBER );
			float dragness = static_cast<float>(lua_tonumber( pLuaState, -1 ));
			DEBUG_PRINT_GAMEPLAY( "The dragness for the gameobject is %.7f", dragness );
			// Pop for dragness
			lua_pop_top( pLuaState );

			// Retrieve the AABB settings
			lua_pushstring( pLuaState, "AABB" );
			result = lua_gettable( pLuaState, -2 );
			assert( result == LUA_TTABLE );

			// Retrieve the center in AABB
			lua_pushstring( pLuaState, "center" );
			result = lua_gettable( pLuaState, -2 );
			assert( result == LUA_TTABLE );
			Point2D<float> center = ParsePointFromLua<float>( pLuaState );
			DEBUG_PRINT_GAMEPLAY( "The center for the AABB is %.3f, %.3f", center.m_x, center.m_y );
			// Pop for the center
			lua_pop_top( pLuaState );

			// Retrive the extends in AABB
			lua_pushstring( pLuaState, "extends" );
			result = lua_gettable( pLuaState, -2 );
			assert( result == LUA_TTABLE );
			Point2D<float> extends = ParsePointFromLua<float>( pLuaState );
			DEBUG_PRINT_GAMEPLAY( "The extends for the AABB is %.3f, %.3f", extends.m_x, extends.m_y );

			// Pop for the extends
			lua_pop_top( pLuaState );

			// Pop for AABB
			lua_pop_top( pLuaState );

			// Retrive the collidable
			lua_pushstring( pLuaState, "collidable" );
			result = lua_gettable( pLuaState, -2 );
			assert( result == LUA_TBOOLEAN );
			bool collidable = lua_toboolean( pLuaState, -1 );
			DEBUG_PRINT_GAMEPLAY( " The collidable for object is %s", collidable ? "true" : "false" );

			// Pop for collidable
			lua_pop_top( pLuaState );

			// Retrive the reflectable
			lua_pushstring( pLuaState, "reflectable" );
			result = lua_gettable( pLuaState, -2 );
			assert( result == LUA_TBOOLEAN );
			bool reflectable = lua_toboolean( pLuaState, -1 );
			DEBUG_PRINT_GAMEPLAY( " The reflectable for object is %s", reflectable ? "true" : "false" );

			// Pop for reflectable
			lua_pop_top( pLuaState );

			// Pop for physics settings
			lua_pop_top( pLuaState );

			// ------- Render -----------
			// Retrieve the go's render settings
			lua_pushstring( pLuaState, "render_settings" );
			result = lua_gettable( pLuaState, -2 );
			assert( result == LUA_TTABLE );

			// Retrieve the spriteName
			lua_pushstring( pLuaState, "sprite_name" );
			result = lua_gettable( pLuaState, -2 );
			assert( result == LUA_TSTRING );
			const char* pSpriteName = lua_tostring( pLuaState, -1 );
			DEBUG_PRINT_GAMEPLAY( "The sprite name for the gameobject is %s", pSpriteName );
			// Pop for sprite's name
			lua_pop_top( pLuaState );

			// Retrieve the spriteSize
			lua_pushstring( pLuaState, "sprite_size" );
			result = lua_gettable( pLuaState, -2 );
			assert( result == LUA_TTABLE );
			Point2D<float> spriteSize = ParsePointFromLua<float>( pLuaState );
			DEBUG_PRINT_GAMEPLAY( "The center for the AABB is %.3f, %.3f", spriteSize.m_x, spriteSize.m_y );
			// Pop for sprite's size
			lua_pop_top( pLuaState );

			// Pop for the render settings
			lua_pop_top( pLuaState );

			DEBUG_PRINT_GAMEPLAY( "-----------Finish printing out the GameObject info for '%s'-------------------", pName );

			// Create the go
			ret = GameObject::Create( pName, Vector3SSE{ initial_position.m_x, initial_position.m_y, 0 } );
			// Set the initial velocity for go.
			ret->SetVelocity( Vector3SSE{ initial_velocity.m_x, initial_velocity.m_y,0 } );

			// Create and assign the AABB to the physicsinfo
			AABB* aabb = AABB::Create( center, extends );
			// Create the player's physics info
			Physics::PhysicsInfo* pPhysicsInfo = Physics::PhysicsInfo::Create( mass, dragness, collidable, reflectable, ret, aabb );
			pPhysicsInfo->SetDrivingForce( Vector3SSE{ force.m_x, force.m_y, 0 } );
			Physics::PhysicsManager::GetInstance().AddPhysicsObject( pPhysicsInfo );

			// Create the assoicated render info
			Render::RenderManager::GetInstance().AddRenderObject( ret, pSpriteName, spriteSize.m_x, spriteSize.m_y );

			// Pop the table at last
			lua_pop_top( pLuaState );
			lua_close( pLuaState );
		}
		delete(pFileContents);
		return ret;
	}
}