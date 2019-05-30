#pragma once
#include "assert.h"
#include "string.h"
#include <crtdbg.h>

namespace Engine
{
	inline HashedString::HashedString() :
		m_Hash( Hash( "" ) )
	{

	}

	inline HashedString::HashedString( const char * i_str ) :
		m_Hash( Hash( i_str ) )
#if defined( DEBUG_KEEP_STRING) && defined(_DEBUG)
		, m_pStr( _strdup( i_str ) )
#endif // DEBUG_KEEP_STRING

	{

	}

	inline HashedString::HashedString( const HashedString & i_other ) :
		m_Hash( i_other.m_Hash )
#if defined( DEBUG_KEEP_STRING) && defined(_DEBUG)
		, m_pStr( _strdup( i_other.m_pStr ) )
#endif // DEBUG_KEEP_STRING
	{
	}

	inline HashedString::HashedString( HashedString && i_other ) :
		m_Hash( i_other.m_Hash )
#if defined( DEBUG_KEEP_STRING) && defined(_DEBUG)
		, m_pStr( i_other.m_pStr )
#endif // DEBUG_KEEP_STRING
	{
#if defined( DEBUG_KEEP_STRING) && defined(_DEBUG)
		i_other.m_pStr = nullptr;
#endif
	}

	inline HashedString & HashedString::operator=( const HashedString & i_other )
	{
		m_Hash = i_other.m_Hash;
#if defined( DEBUG_KEEP_STRING) && defined(_DEBUG)
		if (m_pStr != nullptr)
		{
			delete m_pStr;
		}
		m_pStr = _strdup( i_other.m_pStr );
#endif
		return *this;
	}

	inline HashedString & HashedString::operator=( HashedString && i_other )
	{
		m_Hash = i_other.m_Hash;
#if defined( DEBUG_KEEP_STRING) && defined(_DEBUG) 
		if (m_pStr != nullptr)
		{
			delete m_pStr;
		}
		m_pStr = i_other.m_pStr;
		i_other.m_pStr = nullptr;
#endif
		return *this;
	}

	inline HashedString::~HashedString()
	{
#if defined( DEBUG_KEEP_STRING) && defined(_DEBUG)
		if (m_pStr != nullptr)
		{
			delete m_pStr;
		}
		m_pStr = nullptr;
#endif
	}

	inline bool HashedString::operator==( const HashedString & i_other ) const
	{
		return m_Hash == i_other.m_Hash;
	}

	inline bool HashedString::operator<( const HashedString & i_other ) const
	{
		return m_Hash < i_other.m_Hash;
	}
}