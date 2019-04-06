#pragma once
#include "Point2D.h"
#include "TString.h"
#include "IController.h"

namespace Engine
{
	template<class T>
	class SmartPtr;

	class GameObject
	{
	public:
		static SmartPtr<GameObject>  Create( const TString &, const Point2D<float> & );

		virtual ~GameObject();
		inline const TString & GetName(){ return m_name; };
		inline void SetName( const TString & i_name ) { m_name = i_name; }

		inline const Point2D<float> & GetPosition() { return m_position; }
		inline void SetPosition( const Point2D<float> & i_other ) { m_position = i_other; }

		inline const Point2D<float> & GetVelocity(){ return m_velocity; }
		inline void SetVelocity( const Point2D<float> & i_other ){ m_velocity = i_other; }

		inline const float GetZRot(){ return m_zRot; }
		inline void SetZRot( float i_zRot ){ m_zRot = i_zRot; }

		inline const Point2D<float> GetScale(){ return m_scale; }
		inline void SetScale( float i_scaleX, float i_scaleY ){ m_scale = Point2D<float>{ i_scaleX, i_scaleY }; }

		inline IController * GetController(){ return m_pController; }
		inline void SetController( IController * i_pController ){ m_pController = i_pController; }

		GameObject( const GameObject & ) = delete;
		void operator = ( const GameObject & ) = delete;


		// Temporary solution for gameplay logic to access the constructors for GameObject.
	protected:
		GameObject(){};
		GameObject( const TString &, const Point2D<float> & );

	private:
		TString m_name;
		Point2D<float> m_position;
		Point2D<float> m_velocity;
		Point2D<float> m_scale;
		float m_zRot;
		IController * m_pController;
	};
}