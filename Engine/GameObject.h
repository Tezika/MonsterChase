#pragma once
#include "Vector3SSE.h"
#include "TString.h"
#include "HashedString.h"

namespace Engine
{
	template<class T>
	class SmartPtr;
	struct Matrix4x4;
	class IController;

	class GameObject
	{
	public:
		static SmartPtr<GameObject> Create( const HashedString&, const Vector3SSE& );

		virtual ~GameObject();
		inline const HashedString& GetName() { return m_name; };
		inline void SetName( const HashedString& i_name ) { m_name = i_name; }

		inline const Vector3SSE& GetPosition() { return m_position; }
		inline void SetPosition( const Vector3SSE& i_other ) { m_position = i_other; }

		inline const Vector3SSE& GetVelocity() { return m_velocity; }
		inline void SetVelocity( const Vector3SSE& i_other ) { m_velocity = i_other; }

		inline const float GetZRot() { return m_zRot; }
		inline void SetZRot( float i_zRot ) { m_zRot = i_zRot; }

		inline const Vector3SSE& GetScale() { return m_scale; }
		inline void SetScale( float i_scaleX, float i_scaleY, float i_scaleZ = 1 ) { m_scale = Vector3SSE{ i_scaleX, i_scaleY, i_scaleZ }; }

		inline IController* GetController() { return m_pController; }
		inline void SetController( Engine::IController* i_pController ) { m_pController = i_pController; }

		Matrix4x4 GetMatrixFromLocalToWorld();
		Matrix4x4 GetMatrixFromWorldToLocal();

		GameObject( const GameObject& ) = delete;
		void operator = ( const GameObject& ) = delete;

	protected:
		GameObject() = default;
		GameObject( const HashedString&, const Vector3SSE& );

	private:
		HashedString m_name;
		Vector3SSE m_position;
		Vector3SSE m_velocity;
		Vector3SSE m_scale;
		float m_zRot;
		IController* m_pController;
	};
}