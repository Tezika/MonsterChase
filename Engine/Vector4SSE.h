#pragma once
#include "immintrin.h"

namespace Engine
{
	struct Vector4SSE
	{
	public:
		Vector4SSE(){};
		Vector4SSE( float i_x, float i_y, float i_z, float i_w ) :m_vec( _mm_set_ps( i_w, i_z, i_y, i_x ) ){};
		Vector4SSE( const __m128& i_otherVec ) :m_vec( i_otherVec ){};
		Vector4SSE( const Vector4SSE &  i_other ) : m_vec( i_other.m_vec ){};
		void operator=( const Vector4SSE & i_other ){ m_vec = i_other.m_vec; }

		//Override the arithmetic operator.
		inline Vector4SSE operator+( const Vector4SSE & i_other ) const
		{
			return Vector4SSE( _mm_add_ps( m_vec, i_other.m_vec ) );
		};

		inline void operator+=( const Vector4SSE & i_other ){ m_vec = _mm_add_ps( m_vec, i_other.m_vec ); };

		inline Vector4SSE operator-( const Vector4SSE & i_other ) const
		{
			return Vector4SSE( _mm_sub_ps( m_vec, i_other.m_vec ) );
		};

		inline void operator-=( const Vector4SSE & i_other ){ m_vec = _mm_sub_ps( m_vec, i_other.m_vec ); };

		inline Vector4SSE operator*( float value ) const
		{
			return Vector4SSE( _mm_mul_ps( m_vec, _mm_set1_ps( value ) ) );
		};

		inline void operator*=( float value ) { m_vec = _mm_mul_ps( m_vec, _mm_set1_ps( value ) ); };

		inline Vector4SSE operator/( float value ) const
		{
			assert( value != 0 );
			return Vector4SSE( _mm_div_ps( m_vec, _mm_set1_ps( value ) ) );
		}
		inline void operator/=( float value )
		{
			assert( value != 0 );
			m_vec = _mm_div_ps( m_vec, _mm_set1_ps( value ) );
		};

		inline float Length(){ return _mm_cvtss_f32( _mm_sqrt_ps( _mm_dp_ps( m_vec, m_vec, 0x71 ) ) ); }
		Vector4SSE Normalize();

		// Dot, cross, magnitude method
		friend float Dot( const Vector4SSE & i_lhs, const Vector4SSE & i_rhs );

	private:
		__m128 m_vec;
	};
}