//
//  enemy.cpp
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/9/1.
//  Copyright © 2018 Tezika ZHou. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "enemy.h"
#include "game.h"

using namespace MonsterChase;

Enemy::Enemy() :Object::Object()
{
	next_ = nullptr;
	attack_ = 3;
}

Enemy::Enemy(char* name, int moveSpeed, int health, int attack) :Object::Object(name, moveSpeed, health)
{
	next_ = nullptr;
	attack_ = attack;
}

Enemy::~Enemy()
{
	//    std::cout<<"Desconstruct the enemy: "<< this->GetName() << std::endl;
}

void Enemy::Move()
{
	Object::Move();
	auto player = Game::GetInstance().GetCurPlayer();
	int playerPosX = player->GetPosX();
	int playerPosY = player->GetPosY();

	int xDelta = playerPosX - this->GetPosX();
	int yDelta = playerPosY - this->GetPosY();


	if (abs(xDelta) > abs(yDelta))
	{
		auto moveDis = abs(xDelta) <= this->GetMoveSpeed() ? abs(xDelta) : this->GetMoveSpeed();
		//move horizontally
		if (xDelta > 0)
		{
			//move right
			this->SetPosX(this->GetPosX() + moveDis);
		}
		else if (xDelta < 0)
		{
			//move left
			this->SetPosX(this->GetPosX() - moveDis);
		}
	}
	else
	{
		auto moveDis = abs(yDelta) <= this->GetMoveSpeed() ? abs(yDelta) : this->GetMoveSpeed();
		//move vertically
		if (yDelta > 0)
		{
			//move up
			this->SetPosY(this->GetPosY() + moveDis);

		}
		else if (yDelta < 0)
		{
			//move down
			this->SetPosY(this->GetPosY() - moveDis);
		}
	}

	//Clamp the position
	this->SetPosX(Game::GetInstance().ClampForMap(this->GetPosX(), Game::GetInstance().GetGridWidth()));
	this->SetPosY(Game::GetInstance().ClampForMap(this->GetPosY(), Game::GetInstance().GetGridHeight()));

	//When the enemy finishes one move, its hp decrease by 1.
	this->SetHealth(this->GetHealth() - 1);
}

void Enemy::PrintOutInfo()
{
	Object::PrintOutInfo();
	std::cout << "The " << this->GetName() << " with the attack " << this->GetAttack()
		<<" and the health "<< this->GetHealth() << ", position is  [" << this->GetPosX() << "," << this->GetPosY() << "]." << std::endl;
}

Enemy* Enemy::GetNext()
{
	if (next_ == nullptr)
	{
		return nullptr;
	}
	else
	{
		return next_;
	}
}

void Enemy::SetNext(Enemy* node)
{
	next_ = node;
}
