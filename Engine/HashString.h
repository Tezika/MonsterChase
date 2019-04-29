#pragma once
namespace Engine
{
	class HashedString
	{
	public:
		HashedString();
		~HashedString();

		HashedString( const char * i_str );
		HashedString( const HashedString & i_other );
		HashedString( const HashedString && i_other );

		HashedString & operator=( const HashedString & i_other );
		HashedString & operator=( const HashedString && i_other );

		inline unsigned int Get(){ return m_Hash; }

#ifdef DEBUG_KEEP_STRING
		inline const char * GetString(){ return m_pStr; };
#endif // DEBUG_KEEP_STRING

		static unsigned int Hash( const char * i_str );
		static unsigned int Hash( const void * i_bytes, size_t i_byteCount );

		bool operator==( const HashedString & i_other ) const;
		// Below for STL container compatibility. That's why I cannot use the TString;
		bool operator<( const HashedString & i_other ) const;

	private:
		unsigned int m_Hash;

#ifdef DEBUG_KEEP_STRING
		const char * m_pStr;
#endif
	};
}

#include "HashedString-inl.h"