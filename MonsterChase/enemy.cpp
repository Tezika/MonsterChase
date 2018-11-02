//
//  enemy.cpp
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/9/1.
//  Copyright � 2018 Tezika ZHou. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "enemy.h"
#include "game.h"

using namespace MonsterChase;

Enemy::Enemy() :Object::Object()
{
	m_Attack_ = 3;
}

Enemy::Enemy(char* name, int moveSpeed, int health, int attack) :Object::Object(name, moveSpeed, health)
{
	m_Attack_ = attack;
}

Enemy::~Enemy()
{
}

void Enemy::Move()
{
	Object::Move();
	auto player = Game::GetInstance().GetCurPlayer();
	int xDelta = player->GetPosition().x - this->m_Position_.x;
	int yDelta = player->GetPosition().y - this->m_Position_.y;


	if (abs(xDelta) > abs(yDelta))
	{
		auto moveDis = abs(xDelta) <= this->GetMoveSpeed() ? abs(xDelta) : this->GetMoveSpeed();
		//move horizontally
		if (xDelta > 0)
		{
			//move right
			this->m_Position_ += Point2D<int>(moveDis, 0);
		}
		else if (xDelta < 0)
		{
			//move left
			this->m_Position_ -= Point2D<int>(moveDis, 0);
		}
	}
	else
	{
		auto moveDis = abs(yDelta) <= this->GetMoveSpeed() ? abs(yDelta) : this->GetMoveSpeed();
		//move vertically
		if (yDelta > 0)
		{
			//move up
			this->m_Position_ += Point2D<int>(0, moveDis);

		}
		else if (yDelta < 0)
		{
			//move down
			this->m_Position_ -= Point2D<int>(0, moveDis);
		}
	}

	//Clamp the position
	this->m_Position_ = Point2D<int>(Game::GetInstance().ClampForMap(this->m_Position_.x, Game::GetInstance().GetGridWidth()), Game::GetInstance().ClampForMap(this->m_Position_.y, Game::GetInstance().GetGridHeight()));
	//When the enemy finishes one move, its hp decrease by 1.
	this->SetHealth(this->GetHealth() - 1);
}

void Enemy::PrintOutInfo()
{
	Object::PrintOutInfo();
	std::cout << "The " << this->GetName() << " with the attack " << this->GetAttack()
		<<" and the health "<< this->GetHealth() << ", position is  [" << this->m_Position_.x << "," << this->m_Position_.y<< "]." << std::endl;
}
