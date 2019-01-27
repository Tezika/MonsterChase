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

Enemy::Enemy() :Entity::Entity(), m_attack( 3 )
{
}

Enemy::Enemy( const Engine::TString & i_name, const Engine::Point2D<int> & i_position, int i_health, int i_attack ) :
	Entity::Entity( i_name, i_position, i_health ),
	m_attack( i_attack )
{
}

Enemy::~Enemy()
{
}

void Enemy::PrintOutInfo()
{
	std::cout << "The " << this->GetName() << " with the attack " << this->GetAttack()
		<< " and the health " << this->GetHealth() << ", position is  [" << this->GetPosition().m_x << "," << this->GetPosition().m_y << "]." << std::endl;
}