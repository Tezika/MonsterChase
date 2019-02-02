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
		GameObject( const TString &, const Point2D<float> & );
		GameObject( const GameObject & );
		void operator = ( const GameObject & );
		virtual ~GameObject();

		inline const TString & GetName(){ return m_name; };
		inline void SetName( const TString & i_name ) { m_name = i_name; }

		inline const Point2D<float> & GetPosition() { return m_position; }
		inline void SetPosition( const Point2D<float> & i_other ) { m_position = i_other; }

		inline IController * GetController(){ return m_pController; }
		inline void SetController( IController * i_pController ){ m_pController = i_pController; }
	private:
		TString m_name;
		Point2D<float> m_position;
		IController * m_pController;
	};
}