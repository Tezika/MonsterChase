//
//  Object.h
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/8/30.
//  Copyright � 2018 Tezika ZHou. All rights reserved.
//

#ifndef Object_h
#define Object_h
#include "Point2D.h"
#include "TString.h"


namespace MonsterChase
{
	class Object
	{
	public:
		Object();
		Object(char * name, int moveSpeed, int health);
		virtual ~Object();

		//old school properties
		inline const Engine::Point2D<int> & GetPosition() { return m_position; };
		inline void SetPosition(const Engine::Point2D<int> & pos) { this->m_position = pos; }

		inline const int GetHealth() { return m_health; }
		inline void SetHealth(int health) { m_health = health; }

		inline const int GetMoveSpeed() { return m_moveSpeed; }

		inline const Engine::TString & GetName() { return m_name; }

		virtual void Move();
		virtual void PrintOutInfo();

	private:
		int m_moveSpeed;
		int m_health;
		Engine::TString m_name;

	protected:
		Engine::Point2D<int> m_position;
	};

}

#endif /* Object_h */
