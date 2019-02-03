#pragma once

namespace Engine
{
	class GameObject;

	class IController
	{
	public:
		IController() {};
		virtual void SetGameObject( GameObject & i_other ) = 0;
		virtual void SetGameObject( GameObject * i_pGameObject ) = 0;
		virtual void UpdateGameObject( float i_dt ) = 0;
		virtual ~IController() {};
	};
}
