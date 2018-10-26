//
//  player.cpp
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/9/1.
//  Copyright © 2018 Tezika ZHou. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "player.h"
#include "game.h"

using namespace MonsterChase;

Player::Player() :Object::Object()
{

}

Player::Player(char* name, int moveSpeed, int health) : Object::Object(name, moveSpeed, health)
{

}

Player::~Player()
{
	//    std::cout<<"Desconstruct the player: "<< this->GetName() << std::endl;
}

void Player::Move()
{
	Object::Move();
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


	switch (input) {
	case 'w':
	case 'W':
		this->position_ += Point2D<int>(0, this->GetMoveSpeed());
		break;
	case 's':
	case 'S':
		this->position_ -= Point2D<int>(0, this->GetMoveSpeed());
		break;
	case 'a':
	case 'A':
		this->position_ = Point2D<int>(this->GetMoveSpeed(), 0);
		break;
	case 'd':
	case 'D':
		this->position_ -= Point2D<int>(this->GetMoveSpeed(), 0);
		break;
	case 'q':
	case 'Q':
		Game::GetInstance().TriggerEnd();
		break;
	default:
		std::cout << ":<.The input you did is invalid" << std::endl;
		break;
	}
	this->position_ = Point2D<int>(Game::GetInstance().ClampForMap(this->position_.x, Game::GetInstance().GetGridWidth()), Game::GetInstance().ClampForMap(this->position_.y, Game::GetInstance().GetGridHeight()));

}

void Player::PrintOutInfo()
{
	Object::PrintOutInfo();
	std::cout << "The " << this->GetName() << " current position is  [" << this->position_.x << "," << this->position_.y << "]." << std::endl;
}

