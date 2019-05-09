#include "stdafx.h"
#include "wall.h"

namespace FinalProject
{
	Wall::Wall() :
		Entity::Entity()
	{
	}

	Wall::Wall( const Engine::TString & i_name, const Engine::Vector3SSE & i_position ) :
		Entity::Entity( i_name, i_position )
	{
	}

	Wall::~Wall()
	{
	}
}