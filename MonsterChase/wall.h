#pragma once
#include "entity.h"
#include "Delegate.h"

namespace FinalProject
{
	class Wall : public Entity
	{
	public:
		Wall();
		Wall( const Engine::TString & name, const Engine::Vector3SSE & i_position );
		void SetDead();
		~Wall();
	private:
		Engine::Messaging::Delegate<void*> m_dOnCollision;
		bool m_bDead;
		void OnCollision( void * i_pCollisionInfo );
	};
}