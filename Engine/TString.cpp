#include "stdafx.h"
#include "TString.h"
#include "ConsolePrint.h"


namespace Engine
{
	TString::TString()
		:m_buffer(nullptr),
		m_size(0)
	{
	}

	TString::TString(const TString & i_str)
	{
		m_size = i_str.m_size;
		m_buffer = new char[m_size];
		strcpy_s(m_buffer, m_size, i_str.m_buffer);
	}

	TString::TString(const char * i_pStr)
	{
		m_size = strlen(i_pStr) + 1;
		m_buffer = new char[m_size];
		strcpy_s(m_buffer, m_size, i_pStr);
	}

	char & TString::operator[](unsigned int i_len)
	{
		return m_buffer[i_len];
	}

	void TString::operator=(const TString & i_str)
	{
		m_size = i_str.m_size;
		strcpy_s(m_buffer, m_size, i_str.m_buffer);
	}

	void TString::operator=(const char * i_pStr)
	{
		m_size = strlen(i_pStr) + 1;
		m_buffer = new char[m_size];
		strcpy_s(m_buffer, m_size, i_pStr);
	}

	void TString::operator+=(const TString & i_str)
	{
		size_t newSize = i_str.Length() + this->Length() - 1;
		char* newBuffer = new char[newSize];
		for (size_t i = 0; i < this->Length(); i++)
		{
			newBuffer[i] = m_buffer[i];
		}
		size_t count = this->Length() - 1;
		for (size_t j = 0; j < i_str.Length(); j++)
		{
			newBuffer[j + count] = i_str.m_buffer[j];
		}
		m_size = newSize;
		newBuffer[m_size] = '\0';

		delete[] m_buffer;
		m_buffer = newBuffer;
	}

	void TString::operator+=(const char * i_pStr)
	{
		size_t newSize = strlen(i_pStr) + this->Length() - 1;
		char* newBuffer = new char[newSize];
		for (size_t i = 0; i < this->Length(); i++)
		{
			newBuffer[i] = m_buffer[i];
		}
		size_t count = this->Length() - 1;
		size_t counter = 0;
		while (*i_pStr)
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

	bool operator==(const TString & i_lhs, const TString & i_rhs)
	{
		if (i_lhs.Length() != i_rhs.Length())
		{
			return false;
		}
		else
		{
			for (size_t i = 0; i < i_lhs.Length(); i++)
			{
				if (i_lhs.m_buffer[i] != i_rhs.m_buffer[i])
				{
					return false;
				}
			}
		}
		return true;
	}

	bool operator==(const TString & i_lhs, const char * i_pRhs)
	{
		return strcmp(i_lhs.m_buffer, i_pRhs) == 0 ? true : false;
	}

	std::ostream & operator<<(std::ostream & i_os, const TString & i_str)
	{
		i_os << i_str.m_buffer;
		return i_os;
	}

	TString::~TString()
	{
		delete[] m_buffer;
	}

}
