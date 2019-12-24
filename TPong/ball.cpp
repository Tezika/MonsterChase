#include "ball.h"
#include "CommonUtility.h"
#include "ConsolePrint.h"
#include "Vector3SSE.h"
#include <random>

namespace TPong
{
	void Ball::Shoot()
	{
		using namespace Engine;
		// Reset ball: Random its position, inital velocity
		const float range_velocity_x_max = 300;
		const float range_velocity_x_min = 50;
		const float range_velocity_y_max = 260;
		const float range_velocity_y_min = 0;
		const float range_vertical_position = 60;
		float r = 0;
		// Rand the intial vertical position for the ball.
		float deltaPosition = RandomInRange( -range_vertical_position, range_vertical_position );
		// Rand a value for the velocity.x
		float velocity_x = RandomInRange( range_velocity_x_min, range_velocity_x_max );
		// Rand the sign for the velocity.x based on the 50%.
		r = rand() / static_cast<float>(RAND_MAX);
		if (r >= 0.5f)
		{
			velocity_x = -velocity_x;
		}
		// Rand a value for the velocity.y
		float velocity_y = RandomInRange( range_velocity_y_min, range_velocity_y_max );
		// Rand the sign for the velocity.y based on the 50%.
		r = rand() / static_cast<float>(RAND_MAX);
		if (r >= 0.5f)
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