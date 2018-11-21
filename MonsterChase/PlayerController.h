#pragma once
#include "IController.h"

namespace MonsterChase
{
	class PlayerController : Engine::IController
	{
	public:
		PlayerController();
		void SetGameObject(Engine::GameObject & i_other) override;
		void UpdateGameObject(const Engine::GameObject & i_other) override;

		inline void SetPlayer(Engine::GameObject & i_player) { m_pPlayer = &i_player; }

	protected:
		~PlayerController();

	private:
		Engine::GameObject * m_pPlayer;
		Engine::GameObject * m_pObject;
	};
}
