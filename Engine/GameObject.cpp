#include "stdafx.h"
#include "GameObject.h"

namespace Engine
{
	GameObject::GameObject()
	{

	}

	GameObject::GameObject( const TString & i_otherName, const Point2D<int> & i_otherPosition ) :
		m_name( i_otherName ),
		m_position( i_otherPosition )
	{
		m_posOfSprite = GLibPoint2D{ (float) m_position.m_x, (float) m_position.m_y };
	}

	GameObject::~GameObject()
	{
		if ( m_pController != nullptr )
		{
			delete m_pController;
			m_pController = nullptr;
		}
		if ( m_pSprite != nullptr )
		{
			GLib::Sprites::Release( m_pSprite );
			m_pSprite = nullptr;
		}
	}

	GameObject::GameObject( const GameObject & i_other )
	{
		this->m_name = i_other.m_name;
		this->m_position = i_other.m_position;
		this->m_direction = i_other.m_direction;
	}

	void GameObject::operator=( const GameObject & i_other )
	{
		this->m_name = i_other.m_name;
		this->m_position = i_other.m_position;
		this->m_direction = i_other.m_direction;
	}
}