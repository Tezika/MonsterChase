#pragma once
#include "Point2D.h"
#include "TString.h"
#include "IController.h"

namespace Engine
{
	class GameObject
	{
	public:
		GameObject();
		GameObject( const TString &, const Point2D<int> & );
		GameObject( const GameObject & );
		void operator = ( const GameObject & );
		virtual ~GameObject();

		inline const TString & GetName(){ return m_name; };
		inline void SetName( const TString & i_name ) { m_name = i_name; }

		inline const Point2D<int> & GetPosition() { return m_position; }
		inline void SetPosition( const Point2D<int> & i_other ) { m_position = i_other; }

		inline const Point2D<int> & GetDirection() { return m_direction; }
		inline void SetDirection( const Point2D<int> & i_other ) { m_direction = i_other; }

		inline IController * GetController(){ return m_pController; }
		inline void SetController( IController * i_pController ){ m_pController = i_pController; }
	private:
		TString m_name;
		Point2D<int> m_direction;
		Point2D<int> m_position;
		IController * m_pController;
	};
}