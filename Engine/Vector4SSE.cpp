#include "stdafx.h"
#include "Vector4SSE.h"

namespace Engine
{
	Vector4SSE Vector4SSE::Normalize() const
	{
		float length = this->Length();
		if ( length == 0 )
		{
			return Vector4SSE{ 0, 0, 0, 0 };
		}
		return Vector4SSE( _mm_div_ps( m_vec, _mm_set1_ps( length ) ) );
	}
}
