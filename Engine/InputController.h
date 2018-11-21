#pragma once
#include "IController.h"

namespace Engine
{
	class InputController : IController
	{
	public:
		InputController();
		void UpdateGameObject(const GameObject & i_other) override;
	protected:
		~InputController();
	};
}

