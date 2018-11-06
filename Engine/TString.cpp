#include "stdafx.h"
#include "TString.h"
#include "ConsolePrint.h"


namespace Engine
{
	TString::TString()
	{
		m_buffer = nullptr;
		m_size = 0;
	}

	TString::TString(const TString& str)
	{
		m_size = str.m_size;
		m_buffer = new char[m_size];
		strcpy_s(m_buffer, m_size, str.m_buffer);
	}

	TString::TString(const char* p)
	{
		m_size = strlen(p) + 1;
		m_buffer = new char[m_size];
		strcpy_s(m_buffer, m_size, p);
	}

	char& TString::operator[](unsigned int len)
	{
		return m_buffer[len];
	}

	void TString::operator=(const TString& str)
	{
		m_size = str.m_size;
		strcpy_s(m_buffer, m_size, str.m_buffer);
	}

	void TString::operator=(const char* p)
	{
		m_size = strlen(p) + 1;
		m_buffer = new char[m_size];
		strcpy_s(m_buffer, m_size, p);
	}

	void TString::operator+=(const TString& str)
	{
		size_t newSize = str.Length() + this->Length() - 1;
		char* newBuffer = new char[newSize];
		for (size_t i = 0; i < this->Length(); i++)
		{
			newBuffer[i] = m_buffer[i];
		}
		size_t count = this->Length() - 1;
		for (size_t j = 0; j < str.Length(); j++)
		{
			newBuffer[j + count] = str.m_buffer[j];
		}
		m_size = newSize;
		newBuffer[m_size] = '\0';

		delete[] m_buffer;
		m_buffer = newBuffer;
	}

	void TString::operator+=(const char* p)
	{
		size_t newSize = strlen(p) + this->Length() - 1;
		char* newBuffer = new char[newSize];
		for (size_t i = 0; i < this->Length(); i++)
		{
			newBuffer[i] = m_buffer[i];
		}
		size_t count = this->Length() - 1;
		size_t counter = 0;
		while (*p)
		{
			newBuffer[counter + count] = *p;
			counter++;
			p++;
		}
		m_size = newSize;
		newBuffer[m_size] = '\0';

		delete[] m_buffer;
		m_buffer = newBuffer;
	}

	bool operator==(const TString &lhs, const TString &rhs)
	{
		if (lhs.Length() != rhs.Length())
		{
			return false;
		}
		else
		{
			for (size_t i = 0; i < lhs.Length(); i++)
			{
				if (lhs.m_buffer[i] != rhs.m_buffer[i])
				{
					return false;
				}
			}
		}
		return true;
	}

	bool operator==(const TString &lhs, const char* rhs)
	{
		return strcmp(lhs.m_buffer, rhs) == 0 ? true : false;
	}

	std::ostream & operator<<(std::ostream & os, const TString & str)
	{
		os << str.m_buffer;
		return os;
	}

	TString::~TString()
	{
		delete[] m_buffer;
	}

}
