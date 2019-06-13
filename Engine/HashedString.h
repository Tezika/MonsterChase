#pragma once
namespace Engine
{
#ifndef DEBUG_KEEP_STRING
//#define DEBUG_KEEP_STRING
#endif // !DEBUG_KEEP_STRING

	class HashedString
	{
	public:
		HashedString();
		~HashedString();

		HashedString( const char * i_str );
		HashedString( const HashedString & i_other );
		HashedString( HashedString && i_other );

		HashedString & operator=( const HashedString & i_other );
		HashedString & operator=( HashedString && i_other );

		inline unsigned int Get() { return m_Hash; }

#if defined( DEBUG_KEEP_STRING ) && defined( _DEBUG )
		inline const char * c_str() const { return m_pStr; };
#else
		inline const char * c_str() const { return ""; };
#endif // 

		static unsigned int Hash( const char * i_str );
		static unsigned int Hash( const void * i_bytes, size_t i_byteCount );

		bool operator==( const HashedString & i_other ) const;
		// Below for STL container compatibility. That's why I cannot use the TString;
		bool operator<( const HashedString & i_other ) const;

	private:
		unsigned int m_Hash;

#if defined( DEBUG_KEEP_STRING ) && defined( _DEBUG )
		const char * m_pStr;
#endif
	};
}

#include "HashedString-inl.h"