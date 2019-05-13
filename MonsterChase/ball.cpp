#include "stdafx.h"
#include "ball.h"
#include "CommonUtility.h"
#include "ConsolePrint.h"
#include "Vector3SSE.h"

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

	void Ball::Shoot()
	{
		using namespace Engine;
		// Reset ball: Random its position, inital velocity
		const float range_velocity_x_max = 200;
		const float range_velocity_x_min = 100;
		const float range_velocity_y_max = 200;
		const float range_velocity_y_min = 0;
		const float range_vertical_position = 60;
		float r = 0;
		// Rand the intial vertical position for the ball.
		float deltaPosition = RandomInRange( -range_vertical_position, range_vertical_position );
		// Rand a value for the velocity.x
		float velocity_x = RandomInRange( range_velocity_x_min, range_velocity_x_max );
		// Rand the sign for the velocity.x
		r = rand() / static_cast<float>( RAND_MAX );
		if ( r >= 0.5f )
		{
			velocity_x = -velocity_x;
		}
		// Rand a value for the velocity.y
		float velocity_y = RandomInRange( range_velocity_y_min, range_velocity_y_max );
		// Rand the sign for the velocity.y
		r = rand() / static_cast<float>( RAND_MAX );
		if ( r >= 0.5f )
		{
			velocity_y = -velocity_y;
		}
		Vector3SSE newVelocity = Vector3SSE{ velocity_x, velocity_y, 0 };
		this->SetVelocity( newVelocity );
		this->SetPosition( Vector3SSE{ 0, deltaPosition, 0 } );
		DEBUG_PRINT_GAMEPLAY( "----------Reset the ball successfully.----------" );
	}

	void Ball::Reset()
	{
		using namespace Engine;
		this->SetVelocity( Vector3SSE{ 0,0,0 } );
		this->SetPosition( Vector3SSE{ 0,0,0 } );
	}

	Ball::~Ball()
	{
	}
}