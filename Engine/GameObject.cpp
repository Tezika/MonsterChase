#include "stdafx.h"
#include "GameObject.h"

namespace Engine
{
	GameObject::GameObject()
	{

	}

	GameObject::~GameObject()
	{

	}

	GameObject::GameObject(const GameObject & i_other)
	{
		this->m_position = i_other.m_position;
		this->m_direction = i_other.m_direction;
	}

	void GameObject::operator=(const GameObject & i_other)
	{
		this->m_position = i_other.m_position;
		this->m_direction = i_other.m_direction;
	}
}