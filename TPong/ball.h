#pragma once
#include <Engine/HashedString.h>
#include "entity.h"
namespace TPong
{
	class Ball :public Entity
	{
	public:
		Ball() = default;
		Ball( const Ball& ) = delete;
		Ball& operator=( const Ball& ) = delete;
		void Shoot();
		void Reset();
		virtual ~Ball();
	};
}