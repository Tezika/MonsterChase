#pragma once
#include "entity.h"
#include <Engine/Delegate.h>

namespace TPong
{
	class Wall : public Entity
	{
	public:
		Wall() = default;
		Wall( const Wall& ) = delete;
		Wall& operator=( const Wall& ) = delete;
		void SetDead();
		virtual ~Wall();
	private:
		Engine::Messaging::Delegate<void*> m_dOnCollision;
		bool m_bDead;
		void OnCollision( void* i_pCollisionInfo );
	};
}