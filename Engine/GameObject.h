#pragma once
#include "Vector3.h"
#include "TString.h"
#include "IController.h"

namespace Engine
{
	template<class T>
	class SmartPtr;
	struct Matrix4x4;

	class GameObject
	{
	public:
		static SmartPtr<GameObject>  Create( const TString &, const Vector3 & );

		virtual ~GameObject();
		inline const TString & GetName(){ return m_name; };
		inline void SetName( const TString & i_name ) { m_name = i_name; }

		inline const Vector3 & GetPosition() { return m_position; }
		inline void SetPosition( const Vector3 & i_other ) { m_position = i_other; }

		inline const Vector3 & GetVelocity(){ return m_velocity; }
		inline void SetVelocity( const Vector3 & i_other ){ m_velocity = i_other; }

		inline const float GetZRot(){ return m_zRot; }
		inline void SetZRot( float i_zRot ){ m_zRot = i_zRot; }

		inline const Vector3 & GetScale(){ return m_scale; }
		inline void SetScale( float i_scaleX, float i_scaleY, float i_scaleZ = 1 ){ m_scale = Vector3{ i_scaleX, i_scaleY, i_scaleZ }; }

		inline IController * GetController(){ return m_pController; }
		inline void SetController( IController * i_pController ){ m_pController = i_pController; }

		Matrix4x4 GetMatrixFromLocalToWorld();
		Matrix4x4 GetMatrixFromWorldToLocal();

		GameObject( const GameObject & ) = delete;
		void operator = ( const GameObject & ) = delete;

	protected:
		GameObject(){};
		GameObject( const TString &, const Vector3 & );

	private:
		TString m_name;
		Vector3 m_position;
		Vector3 m_velocity;
		Vector3 m_scale;
		float m_zRot;
		IController * m_pController;
	};
}