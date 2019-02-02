//
//  enemy.h
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/9/1.
//  Copyright © 2018 Tezika ZHou. All rights reserved.
//

#ifndef enemy_h
#define enemy_h
#include "entity.h"

namespace MonsterChase
{
	class Enemy : public Entity
	{
	public:
		Enemy();
		Enemy( const Engine::TString & i_name, const Engine::Point2D<float> & i_position, int i_health, int i_attack );
		~Enemy();

		void SetAttack( int attack ) { m_attack = attack; }
		int  GetAttack() { return m_attack; }

		void PrintOutInfo();
	private:
		int m_attack;

	protected:
	};
}
#endif /* enemy_h */
