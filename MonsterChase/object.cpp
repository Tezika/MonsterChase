//
//  Object.cpp
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/8/30.
//  Copyright © 2018 Tezika ZHou. All rights reserved.
//

#include <stdio.h>
#include "Object.h"
#include "object.h"

using namespace MonsterChase;

Object::Object()
{

}

Object::~Object()
{
}

Object::Object(char* name, int moveSpeed, int health)
{
	name_ = name;
	health_ = health;
	moveSpeed_ = moveSpeed;
}

void Object::Move()
{
}

void Object::PrintOutInfo()
{

}
