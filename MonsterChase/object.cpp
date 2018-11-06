//
//  Object.cpp
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/8/30.
//  Copyright © 2018 Tezika ZHou. All rights reserved.
//

#include <stdio.h>
#include "object.h"


namespace MonsterChase
{
	Object::Object()
	{

	}

	Object::~Object()
	{
	}

	Object::Object(char* name, int moveSpeed, int health)
	{
		m_name = name;
		m_health = health;
		m_moveSpeed = moveSpeed;
	}

	void Object::Move()
	{
	}

	void Object::PrintOutInfo()
	{

	}
}
