#pragma once
#include "GameObject.h"

namespace Engine
{
	class IController
	{
	public:
		IController() {};
		~IController() {};
		virtual void UpdateGameObject(const GameObject & i_other) = 0;
	};
}
