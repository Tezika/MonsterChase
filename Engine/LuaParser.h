#pragma once

namespace Engine
{
	class GameObject;

	template<class T>
	class SmartPtr;

	SmartPtr<GameObject> CreateGameObjectByFile( const char * i_fileName );
}