//
//  player.cpp
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/9/1.
//  Copyright � 2018 Tezika ZHou. All rights reserved.
//

#include <iostream>
#include <math.h>
#include "player.h"
#include "game.h"

namespace FinalProject
{
	Player::Player() : Entity::Entity()
	{

	}

	Player::Player( const Engine::TString & i_name, const Engine::Vector3SSE & i_position ):
		Entity::Entity( i_name, i_position )
	{
	}

	Player::~Player()
	{
		//    std::cout<<"Desconstruct the player: "<< this->GetName() << std::endl;
	}

	void Player::PrintOutInfo()
	{
		Entity::PrintOutInfo();
		std::cout << "The " << this->GetName() << " current position is  [" << this->GetPosition().x() << "," << this->GetPosition().y() << "]." << std::endl;
	}
}