#pragma once
#include "Delegate.h"

namespace TPong
{
	class Wall
	{
	public:
		Wall();
		Wall( const Engine::HashedString & name, const Engine::Vector3SSE & i_position );
		void SetDead();
		virtual ~Wall();
	private:
		Engine::Messaging::Delegate<void*> m_dOnCollision;
		bool m_bDead;
		void OnCollision( void * i_pCollisionInfo );
	};
}