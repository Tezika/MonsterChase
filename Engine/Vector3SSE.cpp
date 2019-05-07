#include "stdafx.h"
#include "Vector3SSE.h"

namespace Engine
{
	inline float Dot( const Vector3SSE & i_lhs, const Vector3SSE & i_rhs )
	{
		return _mm_cvtss_f32( _mm_dp_ps( i_lhs.m_vec, i_lhs.m_vec, 0x71 ) );
	}

	inline Vector3SSE Cross( const Vector3SSE & i_lhs, const Vector3SSE & i_rhs )
	{
		return Vector3SSE(
			_mm_sub_ps(
				_mm_mul_ps( _mm_shuffle_ps( i_lhs.m_vec, i_lhs.m_vec, _MM_SHUFFLE( 3, 0, 2, 1 ) ),
					_mm_shuffle_ps( i_rhs.m_vec, i_rhs.m_vec, _MM_SHUFFLE( 3, 1, 0, 2 ) ) ),
				_mm_mul_ps( _mm_shuffle_ps( i_lhs.m_vec, i_lhs.m_vec, _MM_SHUFFLE( 3, 1, 0, 2 ) ),
					_mm_shuffle_ps( i_rhs.m_vec, i_rhs.m_vec, _MM_SHUFFLE( 3, 0, 2, 1 ) ) )
			) );
	}

	Vector3SSE Vector3SSE::Normalize()
	{
		float length = this->Length();
		assert( length != 0 );
		return Vector3SSE( _mm_div_ps( m_vec, _mm_set1_ps( length ) ) );
	}
}