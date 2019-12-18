#pragma once
#include "SmartPtr.h"

namespace Engine
{
	class GameObject;

	class IController
	{
	public:
		IController() = default;
		virtual void SetControlGameObject( const SmartPtr<GameObject> & i_other ) = 0;
		virtual void UpdateGameObject( float i_dt ) = 0;
		virtual bool IsEnable() = 0;
		virtual void SetEnable( bool bIsEnable ) = 0;
		virtual ~IController() {};
	};
}
