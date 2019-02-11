#pragma once
#include "SmartPtr.h"

namespace Engine
{
	class GameObject;

	class IController
	{
	public:
		IController() {};
		virtual void SetControlGameObject( const SmartPtr<GameObject> & i_other ) = 0;
		virtual void UpdateGameObject( float i_dt ) = 0;
		virtual ~IController() {};
	};
}
