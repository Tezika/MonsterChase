#include "stdafx.h"
#include "Matrix4x4.h"
#include "math.h"
#include "iostream"

namespace Engine
{
	Matrix4x4::Matrix4x4()
	{
#if _DEBUG
		m_matrix[0][0] = NAN;
#endif
	}

	Matrix4x4::~Matrix4x4()
	{

	}

	Matrix4x4::Matrix4x4( const Matrix4x4 & i_other )
	{
		// Cope every spot for the matrix.
		m_matrix[0][0] = i_other.m_matrix[0][0];	m_matrix[0][1] = i_other.m_matrix[0][1];	m_matrix[0][2] = i_other.m_matrix[0][2];	m_matrix[0][3] = i_other.m_matrix[0][3];
		m_matrix[1][0] = i_other.m_matrix[1][0];	m_matrix[1][1] = i_other.m_matrix[1][1];	m_matrix[1][2] = i_other.m_matrix[1][2];	m_matrix[1][3] = i_other.m_matrix[1][3];
		m_matrix[2][0] = i_other.m_matrix[2][0];	m_matrix[2][1] = i_other.m_matrix[2][1];	m_matrix[2][2] = i_other.m_matrix[2][2];	m_matrix[2][3] = i_other.m_matrix[2][3];
		m_matrix[3][0] = i_other.m_matrix[3][0];	m_matrix[3][1] = i_other.m_matrix[3][1];	m_matrix[3][2] = i_other.m_matrix[3][2];	m_matrix[3][3] = i_other.m_matrix[3][3];
	}

	Matrix4x4::Matrix4x4(
		float i_11, float i_12, float i_13, float i_14,
		float i_21, float i_22, float i_23, float i_24,
		float i_31, float i_32, float i_33, float i_34,
		float i_41, float i_42, float i_43, float i_44
	)
	{
		// Initialize the matrix's every spot.
		m_matrix[0][0] = i_11; 	m_matrix[0][1] = i_12;	m_matrix[0][2] = i_13;	m_matrix[0][3] = i_14;
		m_matrix[1][0] = i_21; 	m_matrix[1][1] = i_22;	m_matrix[1][2] = i_23;	m_matrix[1][3] = i_24;
		m_matrix[2][0] = i_31; 	m_matrix[2][1] = i_32;	m_matrix[2][2] = i_33;	m_matrix[2][3] = i_34;
		m_matrix[3][0] = i_41; 	m_matrix[3][1] = i_42;	m_matrix[3][2] = i_43;	m_matrix[3][3] = i_44;
	}

	void Matrix4x4::operator=( const Matrix4x4 & i_other )
	{
		// Cope every spot for the matrix.
		m_matrix[0][0] = i_other.m_matrix[0][0];	m_matrix[0][1] = i_other.m_matrix[0][1];	m_matrix[0][2] = i_other.m_matrix[0][2];	m_matrix[0][3] = i_other.m_matrix[0][3];
		m_matrix[1][0] = i_other.m_matrix[1][0];	m_matrix[1][1] = i_other.m_matrix[1][1];	m_matrix[1][2] = i_other.m_matrix[1][2];	m_matrix[1][3] = i_other.m_matrix[1][3];
		m_matrix[2][0] = i_other.m_matrix[2][0];	m_matrix[2][1] = i_other.m_matrix[2][1];	m_matrix[2][2] = i_other.m_matrix[2][2];	m_matrix[2][3] = i_other.m_matrix[2][3];
		m_matrix[3][0] = i_other.m_matrix[3][0];	m_matrix[3][1] = i_other.m_matrix[3][1];	m_matrix[3][2] = i_other.m_matrix[3][2];	m_matrix[3][3] = i_other.m_matrix[3][3];
	}

	Matrix4x4 Matrix4x4::operator*( const Matrix4x4 & i_other )
	{
		// Assert whether the matrix is available or not.
		assert( !isnan( this->GetM11() ) );
		return Matrix4x4(
			/*M11*/this->GetM11() * i_other.GetM11() + this->GetM12() * i_other.GetM21() + this->GetM13() * i_other.GetM31() + this->GetM14() * i_other.GetM41(),
			/*M12*/this->GetM11() * i_other.GetM12() + this->GetM12() * i_other.GetM22() + this->GetM13() * i_other.GetM32() + this->GetM14() * i_other.GetM42(),
			/*M13*/this->GetM11() * i_other.GetM13() + this->GetM12() * i_other.GetM23() + this->GetM13() * i_other.GetM33() + this->GetM14() * i_other.GetM43(),
			/*M14*/this->GetM11() * i_other.GetM14() + this->GetM12() * i_other.GetM24() + this->GetM13() * i_other.GetM34() + this->GetM14() * i_other.GetM44(),

			/*M21*/this->GetM21() * i_other.GetM11() + this->GetM22() * i_other.GetM21() + this->GetM23() * i_other.GetM31() + this->GetM24() * i_other.GetM41(),
			/*M22*/this->GetM21() * i_other.GetM12() + this->GetM22() * i_other.GetM22() + this->GetM23() * i_other.GetM32() + this->GetM24() * i_other.GetM42(),
			/*M23*/this->GetM21() * i_other.GetM13() + this->GetM22() * i_other.GetM23() + this->GetM23() * i_other.GetM33() + this->GetM24() * i_other.GetM43(),
			/*M24*/this->GetM21() * i_other.GetM14() + this->GetM22() * i_other.GetM24() + this->GetM23() * i_other.GetM34() + this->GetM24() * i_other.GetM44(),


			/*M31*/this->GetM31() * i_other.GetM11() + this->GetM32() * i_other.GetM21() + this->GetM33() * i_other.GetM31() + this->GetM34() * i_other.GetM41(),
			/*M32*/this->GetM31() * i_other.GetM12() + this->GetM32() * i_other.GetM22() + this->GetM33() * i_other.GetM32() + this->GetM34() * i_other.GetM42(),
			/*M33*/this->GetM31() * i_other.GetM13() + this->GetM32() * i_other.GetM23() + this->GetM33() * i_other.GetM33() + this->GetM34() * i_other.GetM43(),
			/*M34*/this->GetM31() * i_other.GetM14() + this->GetM32() * i_other.GetM24() + this->GetM33() * i_other.GetM34() + this->GetM34() * i_other.GetM44(),

			/*M41*/this->GetM41() * i_other.GetM11() + this->GetM42() * i_other.GetM21() + this->GetM43() * i_other.GetM31() + this->GetM44() * i_other.GetM41(),
			/*M42*/this->GetM41() * i_other.GetM12() + this->GetM42() * i_other.GetM22() + this->GetM43() * i_other.GetM32() + this->GetM44() * i_other.GetM42(),
			/*M43*/this->GetM41() * i_other.GetM13() + this->GetM42() * i_other.GetM23() + this->GetM43() * i_other.GetM33() + this->GetM44() * i_other.GetM43(),
			/*M44*/this->GetM41() * i_other.GetM14() + this->GetM42() * i_other.GetM24() + this->GetM43() * i_other.GetM34() + this->GetM44() * i_other.GetM44()
		);
	}

	void Matrix4x4::operator*=( const Matrix4x4 & i_other )
	{
		// Assert whether the matrix is available or not.
		assert( !isnan( this->GetM11() ) );
		m_matrix[0][0] =/*M11*/this->GetM11() * i_other.GetM11() + this->GetM12() * i_other.GetM21() + this->GetM13() * i_other.GetM31() + this->GetM14() * i_other.GetM41();
		m_matrix[0][1] =/*M12*/this->GetM11() * i_other.GetM12() + this->GetM12() * i_other.GetM22() + this->GetM13() * i_other.GetM32() + this->GetM14() * i_other.GetM42();
		m_matrix[0][2] =/*M13*/this->GetM11() * i_other.GetM13() + this->GetM12() * i_other.GetM23() + this->GetM13() * i_other.GetM33() + this->GetM14() * i_other.GetM43();
		m_matrix[0][3] =/*M14*/this->GetM11() * i_other.GetM14() + this->GetM12() * i_other.GetM24() + this->GetM13() * i_other.GetM34() + this->GetM14() * i_other.GetM44();

		m_matrix[1][0] =/*M21*/this->GetM21() * i_other.GetM11() + this->GetM22() * i_other.GetM21() + this->GetM23() * i_other.GetM31() + this->GetM24() * i_other.GetM41();
		m_matrix[1][1] =/*M22*/this->GetM21() * i_other.GetM12() + this->GetM22() * i_other.GetM22() + this->GetM23() * i_other.GetM32() + this->GetM24() * i_other.GetM42();
		m_matrix[1][2] =/*M23*/this->GetM21() * i_other.GetM13() + this->GetM22() * i_other.GetM23() + this->GetM23() * i_other.GetM33() + this->GetM24() * i_other.GetM43();
		m_matrix[1][3] =/*M24*/this->GetM21() * i_other.GetM14() + this->GetM22() * i_other.GetM24() + this->GetM23() * i_other.GetM34() + this->GetM24() * i_other.GetM44();


		m_matrix[2][0] =/*M31*/this->GetM31() * i_other.GetM11() + this->GetM32() * i_other.GetM21() + this->GetM33() * i_other.GetM31() + this->GetM34() * i_other.GetM41();
		m_matrix[2][1] =/*M32*/this->GetM31() * i_other.GetM12() + this->GetM32() * i_other.GetM22() + this->GetM33() * i_other.GetM32() + this->GetM34() * i_other.GetM42();
		m_matrix[2][2] =/*M33*/this->GetM31() * i_other.GetM13() + this->GetM32() * i_other.GetM23() + this->GetM33() * i_other.GetM33() + this->GetM34() * i_other.GetM43();
		m_matrix[2][3] =/*M34*/this->GetM31() * i_other.GetM14() + this->GetM32() * i_other.GetM24() + this->GetM33() * i_other.GetM34() + this->GetM34() * i_other.GetM44();

		m_matrix[3][0] =/*M41*/this->GetM41() * i_other.GetM11() + this->GetM42() * i_other.GetM21() + this->GetM43() * i_other.GetM31() + this->GetM44() * i_other.GetM41();
		m_matrix[3][1] =/*M42*/this->GetM41() * i_other.GetM12() + this->GetM42() * i_other.GetM22() + this->GetM43() * i_other.GetM32() + this->GetM44() * i_other.GetM42();
		m_matrix[3][2] =/*M43*/this->GetM41() * i_other.GetM13() + this->GetM42() * i_other.GetM23() + this->GetM43() * i_other.GetM33() + this->GetM44() * i_other.GetM43();
		m_matrix[3][3] =/*M44*/this->GetM41() * i_other.GetM14() + this->GetM42() * i_other.GetM24() + this->GetM43() * i_other.GetM34() + this->GetM44() * i_other.GetM44();
	}

	Matrix4x4 Matrix4x4::Transpose()
	{
		// Assert whether the matrix is available or not.
		assert( !isnan( this->GetM11() ) );
		return Matrix4x4(
			this->GetM11(), this->GetM21(), this->GetM31(), this->GetM41(),
			this->GetM12(), this->GetM22(), this->GetM32(), this->GetM42(),
			this->GetM13(), this->GetM23(), this->GetM33(), this->GetM43(),
			this->GetM14(), this->GetM24(), this->GetM34(), this->GetM44()
		);
	}

	Matrix4x4 Matrix4x4::Invert()
	{
		// Assert whether the matrix is available or not.
		assert( !isnan( this->GetM11() ) );
		// The algorithm comes from https://github.com/willnode/N-Matrix-Programmer/blob/master/Info/Matrix_4x4.txt
		float a2323 = m_matrix[2][2] * m_matrix[3][3] - m_matrix[2][3] * m_matrix[3][2];
		float a1323 = m_matrix[2][1] * m_matrix[3][3] - m_matrix[2][3] * m_matrix[3][1];
		float a1223 = m_matrix[2][1] * m_matrix[3][2] - m_matrix[2][2] * m_matrix[3][1];
		float a0323 = m_matrix[2][0] * m_matrix[3][3] - m_matrix[2][3] * m_matrix[3][0];
		float a0223 = m_matrix[2][0] * m_matrix[3][2] - m_matrix[2][2] * m_matrix[3][0];
		float a0123 = m_matrix[2][0] * m_matrix[3][1] - m_matrix[2][1] * m_matrix[3][0];
		float a2313 = m_matrix[1][2] * m_matrix[3][3] - m_matrix[1][3] * m_matrix[3][2];
		float a1313 = m_matrix[1][1] * m_matrix[3][3] - m_matrix[1][3] * m_matrix[3][1];
		float a1213 = m_matrix[1][1] * m_matrix[3][2] - m_matrix[1][2] * m_matrix[3][1];
		float a2312 = m_matrix[1][2] * m_matrix[2][3] - m_matrix[1][3] * m_matrix[2][2];
		float a1312 = m_matrix[1][3] * m_matrix[2][3] - m_matrix[1][3] * m_matrix[2][1];
		float a1212 = m_matrix[1][1] * m_matrix[2][2] - m_matrix[1][2] * m_matrix[2][1];
		float a0313 = m_matrix[1][0] * m_matrix[3][3] - m_matrix[1][3] * m_matrix[3][0];
		float a0213 = m_matrix[1][0] * m_matrix[3][2] - m_matrix[1][2] * m_matrix[3][0];
		float a0312 = m_matrix[1][0] * m_matrix[2][3] - m_matrix[1][3] * m_matrix[2][0];
		float a0212 = m_matrix[1][0] * m_matrix[2][2] - m_matrix[1][2] * m_matrix[2][0];
		float a0113 = m_matrix[1][0] * m_matrix[3][1] - m_matrix[1][1] * m_matrix[3][0];
		float a0112 = m_matrix[1][0] * m_matrix[2][1] - m_matrix[1][1] * m_matrix[2][0];

		float det = m_matrix[0][0] * ( m_matrix[1][1] * a2323 - m_matrix[1][2] * a1323 + m_matrix[1][3] * a1223 )
			- m_matrix[0][1] * ( m_matrix[1][0] * a2323 - m_matrix[1][2] * a0323 + m_matrix[1][3] * a0223 )
			+ m_matrix[0][2] * ( m_matrix[1][0] * a1323 - m_matrix[1][1] * a0323 + m_matrix[1][3] * a0123 )
			- m_matrix[0][3] * ( m_matrix[1][0] * a1223 - m_matrix[1][1] * a0223 + m_matrix[1][2] * a0123 );
		assert( det != 0 );
		det = 1 / det;

		return Matrix4x4(
			/*M11*/det * ( m_matrix[1][1] * a2323 - m_matrix[1][2] * a1323 + m_matrix[1][3] * a1223 ),
			/*M12*/det * -( m_matrix[0][1] * a2323 - m_matrix[0][2] * a1323 + m_matrix[0][3] * a1223 ),
			/*M13*/det * ( m_matrix[0][1] * a2313 - m_matrix[0][2] * a1313 + m_matrix[0][3] * a1213 ),
			/*M14*/det * -( m_matrix[0][1] * a2312 - m_matrix[0][2] * a1312 + m_matrix[0][3] * a1212 ),

			/*M21*/det * -( m_matrix[1][0] * a2323 - m_matrix[1][2] * a0323 + m_matrix[1][3] * a0223 ),
			/*M22*/det * ( m_matrix[0][0] * a2323 - m_matrix[0][2] * a0323 + m_matrix[0][3] * a0223 ),
			/*M23*/det * -( m_matrix[0][0] * a2313 - m_matrix[0][2] * a0313 + m_matrix[0][3] * a0213 ),
			/*M24*/det * ( m_matrix[0][0] * a2312 - m_matrix[0][2] * a0312 + m_matrix[0][3] * a0212 ),

			/*M31*/det * ( m_matrix[1][0] * a1323 - m_matrix[1][1] * a0323 + m_matrix[1][3] * a0123 ),
			/*M32*/det * -( m_matrix[0][0] * a1323 - m_matrix[0][1] * a0323 + m_matrix[0][3] * a0123 ),
			/*M33*/det * ( m_matrix[0][0] * a1313 - m_matrix[0][1] * a0313 + m_matrix[0][3] * a0113 ),
			/*M34*/det * -( m_matrix[0][0] * a1312 - m_matrix[0][1] * a0312 + m_matrix[0][3] * a0112 ),

			/*M41*/det * -( m_matrix[1][0] * a1223 - m_matrix[1][1] * a0223 + m_matrix[1][2] * a0123 ),
			/*M42*/det * ( m_matrix[0][0] * a1223 - m_matrix[0][1] * a0223 + m_matrix[0][2] * a0123 ),
			/*M43*/det * -( m_matrix[0][0] * a1213 - m_matrix[0][1] * a0213 + m_matrix[0][2] * a0113 ),
			/*M44*/det * ( m_matrix[0][0] * a1212 - m_matrix[0][1] * a0212 + m_matrix[0][2] * a0112 )

		);
	}
}
