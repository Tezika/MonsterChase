#include "stdafx.h"
#include "Vector4SSE.h"

namespace Engine
{
	// Dot, cross, magnitude method
	inline float Dot( const Vector4SSE & i_lhs, const Vector4SSE & i_rhs )
	{
		return _mm_cvtss_f32( _mm_dp_ps( i_lhs.m_vec, i_lhs.m_vec, 0x71 ) );
	}

	Vector4SSE Vector4SSE::Normalize()
	{
		float length = this->Length();
		assert( length != 0 );
		return Vector4SSE( _mm_div_ps( m_vec, _mm_set1_ps( length ) ) );
	}
}
