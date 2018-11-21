#include "stdafx.h"
#include "GameObject.h"

namespace Engine
{
	GameObject::GameObject()
	{

	}

	GameObject::GameObject(const TString & i_otherName, const Point2D<float> & i_otherPosition) :
		m_name(i_otherName),
		m_position(i_otherPosition)
	{

	}

	GameObject::~GameObject()
	{

	}

	GameObject::GameObject(const GameObject & i_other)
	{
		this->m_name = i_other.m_name;
		this->m_position = i_other.m_position;
		this->m_direction = i_other.m_direction;
	}

	void GameObject::operator=(const GameObject & i_other)
	{
		this->m_name = i_other.m_name;
		this->m_position = i_other.m_position;
		this->m_direction = i_other.m_direction;
	}
}