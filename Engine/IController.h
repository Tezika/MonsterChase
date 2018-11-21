#pragma once

namespace Engine
{
	class GameObject;

	class IController
	{
	public:
		IController() {};
		virtual void SetGameObject(GameObject & i_other) = 0;
		virtual void UpdateGameObject(const GameObject & i_other) = 0;
	protected:
		virtual ~IController() {};
	};
}
