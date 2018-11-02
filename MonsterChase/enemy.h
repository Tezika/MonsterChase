//
//  enemy.h
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/9/1.
//  Copyright © 2018 Tezika ZHou. All rights reserved.
//

#ifndef enemy_h
#define enemy_h
#include "object.h"

namespace MonsterChase
{
	class Enemy : public Object
	{
	public:
		Enemy();
		Enemy(char* name, int moveSpeed, int health, int attack);
		~Enemy();

		void SetAttack(int attack) { m_Attack_ = attack; }
		int  GetAttack() { return m_Attack_; }

	public:
		void Move() override;
		void PrintOutInfo() override;

	private:
		int m_Attack_;

	protected:
	};
}

#endif /* enemy_h */
