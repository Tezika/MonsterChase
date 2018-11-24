#pragma once
#include "PlayerController.h"
#include "game.h"

namespace MonsterChase
{
	PlayerController::PlayerController()
	{

	}

	PlayerController::~PlayerController()
	{

	}

	void PlayerController::UpdateGameObject()
	{
		//Move the object toward the player
		int xDelta = this->m_pPlayer->GetPosition().m_x - this->m_pObject->GetPosition().m_x;
		int yDelta = this->m_pPlayer->GetPosition().m_y - this->m_pObject->GetPosition().m_x;

		const Point2D<int> currentPosition = this->m_pObject->GetPosition();
		if (abs(xDelta) > abs(yDelta))
		{
			auto moveDistance = abs(xDelta) <= this->GetMoveSpeed() ? abs(xDelta) : this->GetMoveSpeed();

			//move horizontally
			if (xDelta > 0)
			{
				//move right
				this->m_pObject->SetPosition(Point2D<int>(moveDistance + currentPosition.m_x, currentPosition.m_y));
			}
			else if (xDelta < 0)
			{
				//move left
				this->m_pObject->SetPosition(Point2D<int>(moveDistance - currentPosition.m_x, currentPosition.m_y));
			}
		}
		else
		{
			auto moveDis = abs(yDelta) <= this->GetMoveSpeed() ? abs(yDelta) : this->GetMoveSpeed();
			//move vertically
			if (yDelta > 0)
			{
				//move up
				this->m_pObject->SetPosition(Point2D<int>(currentPosition.m_x, currentPosition.m_y + moveDis));

			}
			else if (yDelta < 0)
			{
				//move down
				this->m_pObject->SetPosition(Point2D<int>(currentPosition.m_x, currentPosition.m_y - moveDis));
			}
		}

		const Point2D<int> newPosition = this->m_pObject->GetPosition();
		//Clamp the position
		this->m_pObject->SetPosition(Point2D<int>(
			Game::GetInstance().ClampForMap(newPosition.m_x, Game::GetInstance().GetGridWidth()),
			Game::GetInstance().ClampForMap(newPosition.m_y, Game::GetInstance().GetGridHeight())
		));
	}

	void PlayerController::SetGameObject(Engine::GameObject & i_other)
	{
		this->m_pObject = &i_other;
	}
}