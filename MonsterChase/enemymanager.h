//
//  enemymanager.h
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/9/1.
//  Copyright © 2018 Tezika ZHou. All rights reserved.
//

#ifndef enemymanager_h
#define enemymanager_h

#include "enemy.h"
#include "player.h"
namespace MonsterChase
{
	class EnemyManager
	{
	public:
		EnemyManager();
		~EnemyManager();

		Enemy* CreateEnemy();
		Enemy* GetEnemyByName(const char* name);
		bool DestroyAll();
		void MoveEnemies();
		void PrintAllEnemiesInfo();
		void BattleWithPlayer(Player* player);
		void RemoveDiedEnemy();

	private:
		Enemy * head_;
		Enemy* rear_;

		Enemy* InsertEnemy(Enemy* node);
	};
}

#endif /* enemymanager_h */