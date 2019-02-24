#include "stdafx.h"
#include "LuaParser.h"
#include "../Exports/Lua/lua.hpp"
#include "GameObject.h"
#include "SubSystems.h"
#include "Assert.h"
#include "CommonUtility.h"
#include "SmartPtr.h"
#include "ConsolePrint.h"

namespace Engine
{
	SmartPtr<GameObject> CreateGameObjectByFile( const char * i_fileName )
	{
		assert( i_fileName );
		size_t sizeOfFile = 0;
		void * pFileContents = Engine::LoadFile( i_fileName, sizeOfFile );
		if ( pFileContents && sizeOfFile )
		{
			// Create a new lua state
			lua_State * pLuaState = luaL_newstate();
			assert( pLuaState );

			luaL_openlibs( pLuaState );

			int result = 0;

			// Necessary stuff to process our data
			result = luaL_loadbuffer( pLuaState, reinterpret_cast<char *>( pFileContents ), sizeOfFile, nullptr );
			assert( result == 0 );

			result = lua_pcall( pLuaState, 0, 0, 0 );
			assert( result == 0 );

			// Create the player
			result = lua_getglobal( pLuaState, "player" );
			assert( result == LUA_TTABLE );

			// Retrieve the player's name
			lua_pushstring( pLuaState, "name" );
			result = lua_gettable( pLuaState, -2 );
			assert( result == LUA_TSTRING );

			// Printout the player's name
			const char * pName = lua_tostring( pLuaState, -1 );
			DEBUG_PRINT_GAMEPLAY( "The player's name is %s", pName );
			lua_pop( pLuaState, 1 );

			// Retrieve the player's inital position
			lua_pushstring( pLuaState, "initial_position" );
			result = lua_gettable( pLuaState, -2 );
			assert( result == LUA_TTABLE );

			// Iterate the table for player's position
			lua_pushnil( pLuaState );
			while ( lua_next( pLuaState, -2 ) != 0 )
			{
				assert( lua_type( pLuaState, -1 ) == LUA_TNUMBER );

				lua_Number value = lua_tonumber( pLuaState, -1 );
				DEBUG_PRINT_GAMEPLAY( "%f", value );
				// pop the value
				lua_pop( pLuaState, 1 );
			}
			lua_pop( pLuaState, 1 );

			// Pop the table at last
			lua_pop( pLuaState, 1 );
			lua_close( pLuaState );
		}
		delete( pFileContents );
		return SmartPtr<GameObject>( nullptr );
	}


}