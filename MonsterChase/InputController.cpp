#include "stdafx.h"
#include "InputController.h"
#include "Point2D.h"
#include <iostream>
#include "game.h"

namespace MonsterChase
{
	InputController::InputController()
	{

	}

	InputController::~InputController()
	{

	}

	void InputController::UpdateGameObject()
	{
		char input = ' ';
		bool inputValid = false;
		while (!inputValid)
		{
			std::cout << "How do you want to move the player(a/A: Left, s/S: Down, d/D: right, w/W: up) or q/Q for quit?  ";
			std::cin >> input;
			switch (input) {
			case 'w':
			case 'W':
			case 's':
			case 'S':
			case 'a':
			case 'A':
			case 'd':
			case 'D':
			case 'q':
			case 'Q':
				inputValid = true;
				break;
			default:
				std::cout << ":<.The input you did is invalid" << std::endl;
				break;
			}
		}

		const Point2D<int> currentPosition = m_pControlObject->GetPosition();
		switch (input) {
		case 'w':
		case 'W':
			//this->m_position += Point2D<int>(0, this->GetMoveSpeed());
			m_pControlObject->SetPosition(Point2D<int>(currentPosition.m_x, currentPosition.m_y + this->m_moveSpeed));
			break;
		case 's':
		case 'S':
			m_pControlObject->SetPosition(Point2D<int>(currentPosition.m_x, currentPosition.m_y - this->m_moveSpeed));
			break;
		case 'a':
		case 'A':
			m_pControlObject->SetPosition(Point2D<int>(currentPosition.m_x - this->m_moveSpeed, currentPosition.m_y));
			break;
		case 'd':
		case 'D':
			m_pControlObject->SetPosition(Point2D<int>(currentPosition.m_x + this->m_moveSpeed, currentPosition.m_y));
			break;
		case 'q':
		case 'Q':
			Game::GetInstance().TriggerEnd();
			break;
		default:
			std::cout << ":<.The input you did is invalid" << std::endl;
			break;
		}

		const Point2D<int> newPosition = m_pControlObject->GetPosition();
		this->m_pControlObject->SetPosition(Point2D<int>(
			Game::GetInstance().ClampForMap(newPosition.m_x, Game::GetInstance().GetGridWidth()),
			Game::GetInstance().ClampForMap(newPosition.m_y, Game::GetInstance().GetGridHeight())
		));
	}


	void InputController::SetGameObject(Engine::GameObject & i_other)
	{
		this->m_pControlObject = &i_other;
	}
}