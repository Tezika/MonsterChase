//
//  Object.cpp
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/8/30.
//  Copyright © 2018 Tezika ZHou. All rights reserved.
//

#include <stdio.h>
#include "entity.h"


namespace TPong
{
	Entity::Entity()
	{

	}

	Entity::~Entity()
	{
	}

	Entity::Entity( const Engine::HashedString & i_name, const Engine::Vector3SSE & i_position )
	{
		this->SetName( i_name );
		this->SetPosition( i_position );
	}
}
