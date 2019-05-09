#include "stdafx.h"
#include "ball.h"

namespace FinalProject
{
	Ball::Ball() :
		Entity::Entity()
	{
	}

	Ball::Ball( const Engine::TString & i_name, const Engine::Vector3SSE & i_position ) :
		Entity::Entity( i_name, i_position )
	{
	}

	Ball::~Ball()
	{
	}
}