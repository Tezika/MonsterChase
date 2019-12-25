#include "ball.h"
#include "CommonUtility.h"
#include "ConsolePrint.h"
#include "Vector3SSE.h"
#include <random>

namespace TPong
{
	Ball::Ball( const char* i_path_collideSound, const char* i_path_fireSound )
	{
		_ASSERT( i_path_fireSound );
		_ASSERT( i_path_collideSound );
		// Load sounds
		m_sound_collision = Audio::Sound::sSoundSource::Create( i_path_collideSound );
		if (m_sound_collision == nullptr)
		{
			_ASSERT_EXPR( false, L"Failed to load the collision sound." );
		}
		m_sound_fire = Audio::Sound::sSoundSource::Create( i_path_fireSound );
		if (m_sound_fire == nullptr)
		{
			_ASSERT_EXPR( false, L"Failed to load the firing sound." );
		}
		// Register the collision delegate
		this->m_dOnCollision = Engine::Messaging::Delegate<void*>::Create<Ball, & Ball::OnCollision>( this );
		Engine::Messaging::MessageSystem::GetInstance().RegisterMessageDelegate( "OnCollision", this->m_dOnCollision );
	}

	void Ball::Shoot()
	{
		using namespace Engine;
		// Reset ball: Random its position, inital velocity
		constexpr float range_velocity_x_max = 300;
		constexpr float range_velocity_x_min = 50;
		constexpr float range_velocity_y_max = 260;
		constexpr float range_velocity_y_min = 0;
		constexpr float range_vertical_position = 60;
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
		m_go->SetVelocity( newVelocity );
		m_go->SetPosition( Vector3SSE{ 0, deltaPosition, 0 } );
		if (m_sound_fire != nullptr)
		{
			m_sound_fire->Play();
		}
	}

	void Ball::Reset()
	{
		using namespace Engine;
		m_go->SetVelocity( Vector3SSE{ 0,0,0 } );
		m_go->SetPosition( Vector3SSE{ 0,0,0 } );
		DEBUG_PRINT_GAMEPLAY( "----------Reset the ball successfully.----------" );
	}

	void Ball::OnCollision( void* i_pCollisionInfo )
	{
		if (m_sound_collision != nullptr)
		{
			m_sound_collision->Play();
		}
	}

	Ball::~Ball()
	{
		Engine::Messaging::MessageSystem::GetInstance().DeregisterMessageDelegate( "OnCollision", this->m_dOnCollision );
		m_sound_collision = nullptr;
		m_sound_fire = nullptr;
	}
}