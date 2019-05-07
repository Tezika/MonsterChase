#pragma once
#include "Vector4.h"
#include "assert.h"
#include "math.h"

namespace Engine
{
	struct Vector3;

	// Use Right Hand(RH) and column vector(CV) 
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
		Matrix4x4 operator*( const Matrix4x4 & i_other );

		Matrix4x4 operator+( const Matrix4x4 & i_mtx );

		Matrix4x4 operator-( const Matrix4x4 & i_mtx );

		void PrintOut();

		Matrix4x4 Transpose();
		bool Invert( Matrix4x4 & out );

		bool InvertSSE( Matrix4x4 & out ) const;

		void MultiplySSE( const Matrix4x4 & i_other, Matrix4x4 & out ) const;

		static Matrix4x4 CreateScale( float i_xScale, float i_yScale, float i_zScale );
		static Matrix4x4 CreateScale( float i_scale );
		static Matrix4x4 CreateScale( const Vector3 & i_vec_scale );

		static Matrix4x4 CreateRotationX( float i_angle );
		static Matrix4x4 CreateRotationY( float i_angle );
		static Matrix4x4 CreateRotationZ( float i_angle );

		static Matrix4x4 CreateTranslation( const Vector3 & i_vec_translation );
		static Matrix4x4 CreateTranslation( float i_xTranslation, float i_yTranslation, float i_zTranslation );
	private:
		float m_matrix[4][4];
	};

	// Allows us to use V = M * V (i.e. column vector)
	inline Vector4 operator*( const Matrix4x4 & i_mtx, const Vector4 & i_vec )
	{
		assert( i_mtx.GetM11() != NAN );
		return Vector4(
			i_mtx.GetM11() * i_vec.x + i_mtx.GetM12() * i_vec.y + i_mtx.GetM13() * i_vec.z + i_mtx.GetM14() * i_vec.w,
			i_mtx.GetM21() * i_vec.x + i_mtx.GetM22() * i_vec.y + i_mtx.GetM23() * i_vec.z + i_mtx.GetM24() * i_vec.w,
			i_mtx.GetM31() * i_vec.x + i_mtx.GetM32() * i_vec.y + i_mtx.GetM33() * i_vec.z + i_mtx.GetM34() * i_vec.w,
			i_mtx.GetM41() * i_vec.x + i_mtx.GetM42() * i_vec.y + i_mtx.GetM43() * i_vec.z + i_mtx.GetM44() * i_vec.w
		);
	}

	// Allows us to use V = V * M; (i.e. row vector)
	inline Vector4 operator*( const Vector4 & i_vec, const Matrix4x4 & i_mtx )
	{
		return i_mtx * i_vec;
	}

	// Scaler multiplication
	inline Matrix4x4 operator*( const Matrix4x4 & i_mtx, float i_scaler )
	{
		assert( i_mtx.GetM11() != NAN );
		return Matrix4x4(
			i_scaler * i_mtx.GetM11(), i_scaler * i_mtx.GetM12(), i_scaler * i_mtx.GetM13(), i_scaler * i_mtx.GetM14(),
			i_scaler * i_mtx.GetM21(), i_scaler * i_mtx.GetM22(), i_scaler * i_mtx.GetM23(), i_scaler * i_mtx.GetM24(),
			i_scaler * i_mtx.GetM31(), i_scaler * i_mtx.GetM32(), i_scaler * i_mtx.GetM33(), i_scaler * i_mtx.GetM34(),
			i_scaler * i_mtx.GetM41(), i_scaler * i_mtx.GetM42(), i_scaler * i_mtx.GetM43(), i_scaler * i_mtx.GetM44()
		);
	}

	inline Matrix4x4 operator*( float scaler, const Matrix4x4 & i_mtx )
	{
		return i_mtx * scaler;
	}

	// Scaler Division
	inline Matrix4x4 operator/( const Matrix4x4 & i_mtx, float i_scaler )
	{
		assert( i_mtx.GetM11() != NAN );
		assert( i_scaler != 0 );
		return Matrix4x4(
			i_mtx.GetM11() / i_scaler, i_mtx.GetM12() / i_scaler, i_mtx.GetM13() / i_scaler, i_mtx.GetM14() / i_scaler,
			i_mtx.GetM21() / i_scaler, i_mtx.GetM22() / i_scaler, i_mtx.GetM23() / i_scaler, i_mtx.GetM24() / i_scaler,
			i_mtx.GetM31() / i_scaler, i_mtx.GetM32() / i_scaler, i_mtx.GetM33() / i_scaler, i_mtx.GetM34() / i_scaler,
			i_mtx.GetM41() / i_scaler, i_mtx.GetM42() / i_scaler, i_mtx.GetM43() / i_scaler, i_mtx.GetM44() / i_scaler
		);
	}
};