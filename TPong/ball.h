#pragma once
#include <Engine/HashedString.h>
#include <Engine/MessageSystem.h>
#include <ReferenceCounting/SmartPtr.h>
#include <Audio/sSoundSource.h>
#include "entity.h"
namespace TPong
{
	class Ball :public Entity
	{
	public:
		Ball() = default;
		Ball( const char* i_path_collideSound, const char* i_path_fireSound );
		Ball( const Ball& ) = delete;
		Ball& operator=( const Ball& ) = delete;
		void Shoot();
		void Reset();
		virtual ~Ball();
	private:
		void OnCollision( void* i_pCollisionInfo );
		Engine::Messaging::Delegate<void*> m_dOnCollision;
		Engine::SmartPtr<Audio::Sound::sSoundSource> m_sound_collision;
		Engine::SmartPtr<Audio::Sound::sSoundSource> m_sound_fire;
	};
}