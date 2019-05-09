//
//  Object.h
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/8/30.
//  Copyright � 2018 Tezika ZHou. All rights reserved.
//

#pragma once
#include "GameObject.h"


namespace FinalProject
{
	class Entity : public Engine::GameObject
	{
	public:
		Entity();
		Entity( const Engine::TString & i_name, const Engine::Vector3SSE & i_position );
		virtual ~Entity();
	};

}
