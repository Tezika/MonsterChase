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
		inline const Engine::Point2D<int>& GetPosition() { return m_Position_; };
		inline void SetPosition(const Engine::Point2D<int>& pos) { this->m_Position_ = pos; }

		inline const int GetHealth() { return m_Health_; }
		inline void SetHealth(int health) { m_Health_ = health; }

		inline const int GetMoveSpeed() { return m_MoveSpeed_; }

		inline const Engine::TString& GetName() { return m_Name_; }

		virtual void Move();
		virtual void PrintOutInfo();

	private:
		int m_MoveSpeed_;
		int m_Health_;
		Engine::TString m_Name_;

	protected:
		Engine::Point2D<int> m_Position_;
	};

}

#endif /* Object_h */
