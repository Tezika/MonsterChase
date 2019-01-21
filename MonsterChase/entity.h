//
//  Object.h
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/8/30.
//  Copyright � 2018 Tezika ZHou. All rights reserved.
//

#ifndef Object_h
#define Object_h
#include "GameObject.h"


namespace MonsterChase
{
	class Entity : public Engine::GameObject
	{
	public:
		Entity();
		Entity( const Engine::TString & i_name, const Engine::Point2D<int> & i_position, int i_health );
		virtual ~Entity();

		inline const int GetHealth() { return m_health; }
		inline void SetHealth( int health ) { m_health = health; }

		virtual void PrintOutInfo();

	private:
		int m_health;
	};

}

#endif /* Object_h */
