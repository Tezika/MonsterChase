#pragma once
#include <Engine/GameObject.h>
#include <ReferenceCounting/SmartPtr.h>
namespace TPong
{
	class Entity
	{
	public:
		Entity() = default;
		virtual ~Entity();
		inline Engine::SmartPtr<Engine::GameObject> GetGameObject() { return m_go; };
		inline void SetGameObject( Engine::SmartPtr<Engine::GameObject>& i_go ) { m_go = i_go; };
	protected:
		Engine::SmartPtr<Engine::GameObject> m_go;
	};
}