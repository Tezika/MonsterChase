#pragma once
#include "Vector4.h"
namespace Engine
{


	struct Matrix4x4
	{
	public:
		inline float GetM11() const { return m_matrix[0][0]; };
		inline float GetM12() const { return m_matrix[0][1]; };
		inline float GetM13() const { return m_matrix[0][2]; };
		inline float GetM14() const { return m_matrix[0][3]; };

		inline float GetM21() const { return m_matrix[1][0]; };
		inline float GetM22() const { return m_matrix[1][1]; };
		inline float GetM23() const { return m_matrix[1][2]; };
		inline float GetM24() const { return m_matrix[1][3]; };

		inline float GetM31() const { return m_matrix[2][0]; };
		inline float GetM32() const { return m_matrix[2][1]; };
		inline float GetM33() const { return m_matrix[2][2]; };
		inline float GetM34() const { return m_matrix[2][3]; };

		inline float GetM41() const { return m_matrix[3][0]; };
		inline float GetM42() const { return m_matrix[3][1]; };
		inline float GetM43() const { return m_matrix[3][2]; };
		inline float GetM44() const { return m_matrix[3][3]; };

		Matrix4x4();
		Matrix4x4(
			float i_11, float i_12, float i_13, float i_14,
			float i_21, float i_22, float i_23, float i_24,
			float i_31, float i_32, float i_33, float i_34,
			float i_41, float i_42, float i_43, float i_44
		);

		Matrix4x4( const Matrix4x4 & i_other );
		void operator=( const Matrix4x4 & i_other );
		~Matrix4x4();

		void operator*=( const Matrix4x4 & i_other );
		Matrix4x4  operator*( const Matrix4x4 & i_other );

		Matrix4x4 Transpose();
		Matrix4x4 Invert();

	private:
		float m_matrix[4][4];
	};

	// Allows us to use V = M * V (i.e. column vector)
	inline Vector4 operator*( const Matrix4x4 & i_mtx, const Vector4 & i_vec )
	{
	}

	// Allows us to use V = V * M; (i.e. row vector)
	inline Vector4 operator*( const Vector4 & i_vec, const Matrix4x4 & i_mtx )
	{
	}
};