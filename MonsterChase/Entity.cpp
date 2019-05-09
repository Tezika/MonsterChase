//
//  Object.cpp
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/8/30.
//  Copyright © 2018 Tezika ZHou. All rights reserved.
//

#include <stdio.h>
#include "entity.h"


namespace FinalProject
{
	Entity::Entity()
	{

	}

	Entity::~Entity()
	{
	}

	Entity::Entity( const Engine::TString & i_name, const Engine::Vector3SSE & i_position, int i_health )
		:m_health( i_health )
	{
		this->SetName( i_name );
		this->SetPosition( i_position );
	}

	void Entity::PrintOutInfo()
	{

	}
}
