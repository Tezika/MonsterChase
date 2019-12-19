#pragma once
#include "entity.h"

namespace TPong
{
	class Ball : public Entity
	{
	public:
		Ball();
		Ball( const Engine::HashedString & i_name, const Engine::Vector3SSE & i_position );
		void Shoot();
		void Reset();
		~Ball();
	};
}