//
//  Object.h
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/8/30.
//  Copyright © 2018 Tezika ZHou. All rights reserved.
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
		inline const Point2D& GetPosition() { return position_; };
		inline void SetPosition(const Point2D& pos) { this->position_ = pos; }

		inline const int GetHealth() { return health_; }
		inline void SetHealth(int health) { health_ = health; }

		inline const int GetMoveSpeed() { return moveSpeed_; }

		inline const TString& GetName() { return name_; }

		virtual void Move();
		virtual void PrintOutInfo();

	private:
		int moveSpeed_;
		int health_;
		TString name_;

	protected:
		Point2D position_;
	};

}

#endif /* Object_h */
