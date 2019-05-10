#include "stdafx.h"
#include "TString.h"
#include "ConsolePrint.h"
#include "Assert.h"
#include "MemorySystem.h"


namespace Engine
{
	TString::TString()
		:m_buffer( nullptr ),
		m_size( 0 )
	{
	}

	TString::TString( const TString & i_str )
	{
		m_size = i_str.m_size;
		m_buffer = new char[m_size];
		strcpy_s( m_buffer, m_size, i_str.m_buffer );
	}

	TString::TString( const char * i_pStr )
	{
		m_size = strlen( i_pStr ) + 1;
		m_buffer = new char[m_size];
		strcpy_s( m_buffer, m_size, i_pStr );
	}

	char & TString::operator[]( unsigned int i_len )
	{
		return m_buffer[i_len];
	}

	void TString::operator=( const TString & i_str )
	{
		if ( m_buffer != nullptr )
		{
			delete[] m_buffer;
		}
		m_size = i_str.m_size;
		m_buffer = new char[m_size];
		strcpy_s( m_buffer, m_size, i_str.m_buffer );
	}

	bool TString::operator==( const TString & i_str ) const
	{
		if ( this->Length() != i_str.Length() )
		{
			return false;
		}
		else
		{
			return strcmp( this->GetBuffer(), i_str.GetBuffer() ) == 0;
		}
		return true;
	}

	void TString::operator=( const char * i_pStr )
	{
		if ( m_buffer != nullptr )
		{
			delete[] m_buffer;
		}
		m_size = strlen( i_pStr ) + 1;
		m_buffer = new char[m_size];
		strcpy_s( m_buffer, m_size, i_pStr );
	}

	void TString::operator+=( const TString & i_str )
	{
		size_t newSize = i_str.Length() + this->Length() - 1;
		char* newBuffer = new char[newSize];
		for ( size_t i = 0; i < this->Length(); i++ )
		{
			newBuffer[i] = m_buffer[i];
		}
		size_t count = this->Length() - 1;
		for ( size_t j = 0; j < i_str.Length(); j++ )
		{
			newBuffer[j + count] = i_str.m_buffer[j];
		}
		m_size = newSize;
		newBuffer[m_size] = '\0';

		delete[] m_buffer;
		m_buffer = newBuffer;
	}

	void TString::operator+=( const char * i_pStr )
	{
		size_t newSize = strlen( i_pStr ) + this->Length() - 1;
		char* newBuffer = new char[newSize];
		for ( size_t i = 0; i < this->Length(); i++ )
		{
			newBuffer[i] = m_buffer[i];
		}
		size_t count = this->Length() - 1;
		size_t counter = 0;
		while ( *i_pStr )
		{
			newBuffer[counter + count] = *i_pStr;
			counter++;
			i_pStr++;
		}
		m_size = newSize;
		newBuffer[m_size] = '\0';

		delete[] m_buffer;
		m_buffer = newBuffer;
	}

	bool operator==( const TString & i_lhs, const TString & i_rhs )
	{
		return i_lhs.operator==(i_rhs);
	}

	bool operator==( const TString & i_lhs, const char * i_pRhs )
	{
		return strcmp( i_lhs.m_buffer, i_pRhs ) == 0 ? true : false;
	}

	std::ostream & operator<<( std::ostream & i_os, const TString & i_str )
	{
		i_os << i_str.m_buffer;
		return i_os;
	}

	std::istream & operator>>( std::istream & i_is, TString & i_str )
	{
		uint8_t inputSize = 100;
		char * input = new char[inputSize];
		i_is >> input;
		uint8_t size = 0;
		while ( input[size] != '\0' )
		{
			size++;
		}
		size++;
		//Use a temporary buffer as meta buffer.
		char * temporaryBuffer = new char[size];
		for ( uint8_t i = 0; i < size - 1; i++ )
		{
			temporaryBuffer[i] = input[i];
		}
		temporaryBuffer[size - 1] = '\0';
		i_str.SetBuffer( temporaryBuffer );

		delete[] input;
		input = nullptr;
		delete[] temporaryBuffer;
		temporaryBuffer = nullptr;
		return i_is;
	}

	void TString::SetBuffer( const char * pBuffer )
	{
		assert( pBuffer != nullptr );
		m_size = strlen( pBuffer ) + 1;
		m_buffer = new char[m_size];
		strcpy_s( m_buffer, m_size, pBuffer );
	}

	TString::~TString()
	{
		delete[] m_buffer;
		m_buffer = nullptr;
	}
}