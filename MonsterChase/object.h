//
//  Object.h
//  MonsterChase
//
//  Created by  TezikaZhou on 2018/8/30.
//  Copyright © 2018 Tezika ZHou. All rights reserved.
//

#ifndef Object_h
#define Object_h

namespace MonsterChase
{
	class Object
	{
	public:
		Object();
		Object(char* name, int moveSpeed, int health);
		virtual ~Object();

		//old school properties
		const int GetPosX() { return pos_x_; }
		void SetPosX(int val) { pos_x_ = val; }

		const int GetPosY() { return pos_y_; }
		void SetPosY(int val) { pos_y_ = val; }

		const char* GetName() { return name_; }
		void SetName(char* name) { name_ = name; }

		const int GetHealth() { return health_; }
		void SetHealth(int health) { health_ = health; }

		const int GetMoveSpeed() { return moveSpeed_; }

		virtual void Move();
		virtual void PrintOutInfo();

	private:
		int pos_x_;
		int pos_y_;
		int moveSpeed_;
		int health_;
		char* name_;

	protected:
	};

}


#endif /* Object_h */
