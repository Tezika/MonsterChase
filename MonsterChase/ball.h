#pragma once
#include "entity.h"

namespace FinalProject
{
	class Ball : public Entity
	{
	public:
		Ball();
		Ball( const Engine::TString & name, const Engine::Vector3SSE & i_position );
		void Reset();
		~Ball();
	};
}