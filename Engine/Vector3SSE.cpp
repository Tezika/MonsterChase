#include "stdafx.h"
#include "Vector3SSE.h"

namespace Engine
{
	Vector3SSE Vector3SSE::Normalize() const
	{
		float length = this->Length();
		if ( length == 0 )
		{
			return Vector3SSE{ 0,0,0 };
		}
		return Vector3SSE( _mm_div_ps( m_vec, _mm_set1_ps( length ) ) );
	}

	Vector3SSE Vector3SSE::Reflect( const Vector3SSE & i_normal ) const
	{
		Vector3SSE n = i_normal.Normalize();
		Vector3SSE res = *this - 2 * ( Dot( *this, n ) ) * n;
		return res;
	}
}