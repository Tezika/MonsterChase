//
//  enemy.h
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/9/1.
//  Copyright © 2018 Tezika ZHou. All rights reserved.
//

#pragma once
#include "entity.h"

namespace MonsterChase
{
	class Enemy : public Entity
	{
	public:
		Enemy();
		Enemy( const Engine::TString & i_name, const Engine::Vector3 & i_position, int i_health, int i_attack );
		~Enemy();

		void SetAttack( int attack ) { m_attack = attack; }
		int  GetAttack() { return m_attack; }

		void PrintOutInfo();
	private:
		int m_attack;

	protected:
	};
}
