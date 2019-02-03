#include "stdafx.h"
#include "GameObject.h"

namespace Engine
{
	GameObject::GameObject()
	{

	}

	GameObject::GameObject( const TString & i_otherName, const Point2D<float> & i_otherPosition ) :
		m_name( i_otherName ),
		m_position( i_otherPosition ),
		// Set the initial velocity as zero
		m_velocity( Point2D<float>( 0, 0 ) )
	{
	}

	GameObject::~GameObject()
	{
		if ( m_pController != nullptr )
		{
			delete m_pController;
			m_pController = nullptr;
		}
	}

	GameObject::GameObject( const GameObject & i_other )
	{
		this->m_name = i_other.m_name;
		this->m_position = i_other.m_position;
		this->m_velocity = i_other.m_velocity;
	}

	void GameObject::operator=( const GameObject & i_other )
	{
		this->m_name = i_other.m_name;
		this->m_position = i_other.m_position;
		this->m_velocity = i_other.m_velocity;
	}
}