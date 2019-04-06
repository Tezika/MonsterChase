#include "stdafx.h"
#include "GameObject.h"
#include "SmartPtr.h"

namespace Engine
{
	SmartPtr<GameObject> GameObject::Create( const TString & i_otherName, const Point2D<float> & i_otherPosition )
	{
		return SmartPtr<GameObject>( new GameObject( i_otherName, i_otherPosition ) );
	}

	GameObject::GameObject( const TString & i_otherName, const Point2D<float> & i_otherPosition ) :
		m_name( i_otherName ),
		m_position( i_otherPosition ),
		// Set the initial velocity as zero
		m_velocity( Point2D<float>( 0, 0 ) ),
		m_scale( Point2D<float>( 1, 1 ) ),
		m_zRot( 0 )
	{
	}

	GameObject::~GameObject()
	{
		if ( m_pController != nullptr )
		{
			m_pController = nullptr;
		}
	}
}