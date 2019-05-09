#pragma once
#include "entity.h"

namespace FinalProject
{
	class Wall : public Entity
	{
	public:
		Wall();
		Wall( const Engine::TString & name, const Engine::Vector3SSE & i_position );
		~Wall();
	};
}