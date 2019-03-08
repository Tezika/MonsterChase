#include "stdafx.h"
#include "Matrix4x4.h"

namespace Engine
{
	Matrix4x4::Matrix4x4()
	{
	}

	Matrix4x4::~Matrix4x4()
	{

	}

	Matrix4x4::Matrix4x4(
		float i_11, float i_12, float i_13, float i_14,
		float i_21, float i_22, float i_23, float i_24,
		float i_31, float i_32, float i_33, float i_34,
		float i_41, float i_42, float i_43, float i_44
	)
	{
		// Initialize the matrix's every spot
		m_matrix[0][0] = i_11; 	m_matrix[0][1] = i_12;	m_matrix[0][2] = i_13;	m_matrix[0][3] = i_14;
		m_matrix[1][0] = i_21; 	m_matrix[1][1] = i_22;	m_matrix[1][2] = i_23;	m_matrix[1][3] = i_24;
		m_matrix[2][0] = i_31; 	m_matrix[2][1] = i_32;	m_matrix[2][2] = i_33;	m_matrix[2][3] = i_34;
		m_matrix[3][0] = i_41; 	m_matrix[3][1] = i_42;	m_matrix[3][2] = i_43;	m_matrix[3][3] = i_44;
	}
}