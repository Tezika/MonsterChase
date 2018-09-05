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

		Enemy* GetNext();
		void SetNext(Enemy* node);

		void SetAttack(int attack) { attack_ = attack; }
		int  GetAttack() { return attack_; }

	public:
		void Move() override;
		void PrintOutInfo() override;

	private:
		Enemy * next_;
		int attack_;

	protected:
	};
}

#endif /* enemy_h */
