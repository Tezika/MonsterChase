#include "stdafx.h"
#include "GameObject.h"
#include "SmartPtr.h"
#include "Matrix4x4.h"
#include "Vector3.h"

namespace Engine
{
	SmartPtr<GameObject> GameObject::Create( const HashedString & i_otherName, const Vector3SSE & i_otherPosition )
	{
		return SmartPtr<GameObject>( new GameObject( i_otherName, i_otherPosition ) );
	}

	GameObject::GameObject( const HashedString & i_otherName, const Vector3SSE & i_otherPosition ) :
		m_name( i_otherName ),
		m_position( i_otherPosition ),
		// Set the initial velocity as zero
		m_velocity( Vector3SSE{ 0.0f,0.0,0.0f } ),
		m_scale( Vector3SSE{ 1.0, 1.0, 1.0f } ),
		m_zRot( 0 )
	{
	}

	Matrix4x4 GameObject::GetMatrixFromLocalToWorld()
	{
		Matrix4x4 mtx_translation = Matrix4x4::CreateTranslation( m_position.x(), m_position.y(), m_position.z() );
		Matrix4x4 mtx_zRotation = Matrix4x4::CreateRotationZ( m_zRot );
		// Remove the scale temporarily
		//Matrix4x4 mtx_scaling = Matrix4x4::CreateScale( m_scale.x, m_scale.y, m_scale.z );
		Matrix4x4 mtx_localToWorld;
		// Change the common matrix multiply into the SSE version.
		mtx_translation.MultiplySSE( mtx_zRotation, mtx_localToWorld );
		return mtx_localToWorld;
	}

	Matrix4x4 GameObject::GetMatrixFromWorldToLocal()
	{
		Matrix4x4 mtx_invert_translation = Matrix4x4::CreateTranslation( -m_position.x(), -m_position.y(), -m_position.z() );
		Matrix4x4 mtx_zRotation = Matrix4x4::CreateRotationZ( m_zRot );
		Matrix4x4 mtx_transpose_zRotation = mtx_zRotation.Transpose();
		// Change the common matrix multiply into the SSE version.
		Matrix4x4 mtx_worldToLocal;
		mtx_transpose_zRotation.MultiplySSE( mtx_invert_translation, mtx_worldToLocal );
		return mtx_worldToLocal;
	}

	GameObject::~GameObject()
	{
		if (m_pController != nullptr)
		{
			m_pController = nullptr;
		}
	}
}