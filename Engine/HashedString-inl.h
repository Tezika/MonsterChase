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
#ifdef DEBUG_KEEP_STRING
		, m_pStr( strdup( i_str ) )
#endif // DEBUG_KEEP_STRING

	{

	}

	inline HashedString::HashedString( const HashedString & i_other ) :
		m_Hash( i_other.m_Hash )
#ifdef DEBUG_KEEP_STRING
		, m_pStr( strdup( i_other.m_pStr ) )
#endif // DEBUG_KEEP_STRING
	{
	}

	inline HashedString::HashedString( const HashedString && i_other ) :
		m_Hash( i_other.m_Hash )
#ifdef DEBUG_KEEP_STRING
		, m_pStr( i_other.m_pStr )
#endif // DEBUG_KEEP_STRING
	{
#ifdef DEBUG_KEEP_STRING
		i_other.m_pStr = nullptr;
#endif
	}

	inline HashedString & HashedString::operator=( const HashedString & i_other )
	{
		m_Hash = i_other.m_Hash;
#ifdef DEBUG_KEEP_STRING
		if ( m_pStr != nullptr )
		{
			delete m_pStr;
		}
		m_pStr = strdup( i_other.m_ptr );
#endif
		return *this;
	}

	inline HashedString & HashedString::operator=( const HashedString && i_other )
	{
		m_Hash = i_other.m_Hash;
#ifdef DEBUG_KEEP_STRING
		if ( m_pStr !=  nullptr)
		{
			delete m_pStr;
		}
		m_pStr = i_other.m_ptr;
		i_other.m_ptr = nullptr;
#endif
		return *this;
	}

	inline HashedString::~HashedString()
	{
#ifdef DEBUG_KEEP_STRING
		if ( m_pStr != nullptr )
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