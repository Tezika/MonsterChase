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
#include "TList.h"

using namespace Engine;

namespace MonsterChase
{
	class EnemyManager
	{
	public:
		EnemyManager();
		~EnemyManager();

		Enemy* GetEnemyByName(const char* name);
		bool DestroyAll();
		void MoveEnemies();
		void PrintAllEnemiesInfo();
		void BattleWithPlayer(Player* player);
		void RemoveDiedEnemy();
		Enemy* CreateEnemy();

	private:
		TList<Enemy>* enemyList_;
		Enemy * head_;
		Enemy* rear_;
		Enemy* InsertEnemy(Enemy* node);

	};
}

#endif /* enemymanager_h */