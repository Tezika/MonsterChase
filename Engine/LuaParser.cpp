#include "stdafx.h"
#include "LuaParser.h"
#include "../Exports/Lua/lua.hpp"
#include "GameObject.h"
#include "SubSystems.h"
#include "Assert.h"
#include "CommonUtility.h"
#include "SmartPtr.h"

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

		}
		return SmartPtr<GameObject>( nullptr );
	}
}