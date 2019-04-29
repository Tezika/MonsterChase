#include "stdafx.h"
#include "HashString.h"
#include "assert.h"

namespace Engine
{
//	HashedString::HashedString() :
//		m_Hash( Hash( "" ) )
//	{
//
//	}
//
//	HashedString::HashedString( const char * i_str ) :
//		m_Hash( Hash( i_str ) )
//#ifdef DEBUG_KEEP_STRING
//		, m_pStr( strdup( i_str ) )
//#endif // DEBUG_KEEP_STRING
//
//	{
//
//	}
//
//	HashedString::HashedString( const HashedString & i_other ) :
//		m_Hash( i_other.m_Hash )
//#ifdef DEBUG_KEEP_STRING
//		, m_pStr( strdup( i_other.m_pStr ) )
//#endif // DEBUG_KEEP_STRING
//	{
//
//	}
//
//	HashedString::HashedString( const HashedString && i_other ) :
//		m_Hash( i_other.m_Hash )
//#ifdef DEBUG_KEEP_STRING
//		, m_pStr( i_other.m_pStr )
//#endif // DEBUG_KEEP_STRING
//	{
//#ifdef DEBUG_KEEP_STRING
//		i_other.m_pStr = nullptr;
//#endif
//	}
//
//	HashedString & HashedString::operator=( const HashedString & i_other )
//	{
//		m_Hash = i_other.m_Hash;
//#ifdef DEBUG_KEEP_STRING
//		if ( m_pStr nullptr != nullptr )
//		{
//			free( m_pStr );
//		}
//		m_pStr = strdup( i_other.m_ptr );
//#endif
//		return *this;
//	}
//
//	HashedString & HashedString::operator=( const HashedString && i_other )
//	{
//		m_Hash = i_other.m_Hash;
//#ifdef DEBUG_KEEP_STRING
//		if ( m_pStr != )
//		{
//			free( m_pStr );
//		}
//
//		m_pStr = i_other.m_ptr;
//		i_other.m_ptr = nullptr;
//#endif
//		return *this;
//	}
//
//	HashedString::~HashedString()
//	{
//#ifdef DEBUG_KEEP_STRING
//		if ( m_pStr != )
//		{
//			free( m_pStr );
//		}
//		m_pStr = nullptr;
//#endif
//	}
//
//	bool HashedString::operator==( const HashedString & i_other ) const
//	{
//		return m_Hash == i_other.m_Hash;
//	}
//
//	bool HashedString::operator<( const HashedString & i_other ) const
//	{
//		return m_Hash < i_other.m_Hash;
//	}
//
	unsigned int HashedString::Hash( const char * i_str )
	{
		return Hash( reinterpret_cast<void *>( const_cast<char*>( i_str ) ), strlen( i_str ) );
	}

	unsigned int HashedString::Hash( const void * i_bytes, size_t i_bytecount )
	{
		// FNV hash, http://isthe.com/chongo/tech/comp/fnv/

		register const unsigned char * p = static_cast<const unsigned char *>( i_bytes );
		unsigned int hash = 2166136261;

		for ( size_t i = 0; i < i_bytecount; ++i )
			hash = 16777619 * ( hash ^ p[i] );

		return hash ^ ( hash >> 16 );
	};

}