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
		Object(char* name, int moveSpeed, int health);
		virtual ~Object();

		//old school properties
		inline const Engine::Point2D<int>& GetPosition() { return position_; };
		inline void SetPosition(const Engine::Point2D<int>& pos) { this->position_ = pos; }

		inline const int GetHealth() { return m_Health_; }
		inline void SetHealth(int health) { m_Health_ = health; }

		inline const int GetMoveSpeed() { return m_MoveSpeed_; }

		inline const Engine::TString& GetName() { return name_; }

		virtual void Move();
		virtual void PrintOutInfo();

	private:
		int moveSpeed_;
		int health_;
		Engine::TString name_;

	protected:
		Engine::Point2D<int> position_;
	};

}

#endif /* Object_h */
