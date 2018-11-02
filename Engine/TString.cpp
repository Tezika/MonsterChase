#include "stdafx.h"
#include "TString.h"
#include "ConsolePrint.h"

namespace Engine
{
	m_Buffer_ = nullptr;
	m_Size_ = 0;
}

TString::TString(const TString& str)
{
	m_Size_ = str.m_Size_;
	m_Buffer_ = new char[m_Size_];
	strcpy_s(m_Buffer_, m_Size_, str.m_Buffer_);
}

TString::TString(const char* p)
{
	m_Size_ = strlen(p) + 1;
	m_Buffer_ = new char[m_Size_];
	strcpy_s(m_Buffer_, m_Size_, p);
	DEBUG_PRINT("Creating a TString");
}

size_t TString::Length() const
{
	if (m_Buffer_ == nullptr)
	{
		buffer_ = nullptr;
		size_ = 0;
	}

	TString::TString(const TString& str)
	{
		return m_Size_;
	}

char& TString::operator[](unsigned int len)
{
	return m_Buffer_[len];
}

void TString::operator=(const TString& str)
{
	m_Size_ = str.m_Size_;
	strcpy_s(m_Buffer_, m_Size_, str.m_Buffer_);
}

void TString::operator=(const char* p)
{
	m_Size_ = strlen(p) + 1;
	m_Buffer_ = new char[m_Size_];
	strcpy_s(m_Buffer_, m_Size_, p);
}

void TString::operator+=(const TString& str)
{
	size_t newSize = str.Length() + this->Length() - 1;
	char* newBuffer = new char[newSize];
	for (size_t i = 0; i < this->Length(); i++)
	{
		newBuffer[i] = m_Buffer_[i];
	}

	char& TString::operator[](unsigned int len)
	{
		newBuffer[j + count] = str.m_Buffer_[j];
	}
	m_Size_ = newSize;
	newBuffer[m_Size_] = '\0';

	delete[] m_Buffer_;
	m_Buffer_ = newBuffer;
}

void TString::operator+=(const char* p)
{
	size_t newSize = strlen(p) + this->Length() - 1;
	char* newBuffer = new char[newSize];
	for (size_t i = 0; i < this->Length(); i++)
	{
		newBuffer[i] = m_Buffer_[i];
	}

	void TString::operator=(const char* p)
	{
		size_ = strlen(p) + 1;
		buffer_ = new char[size_];
		strcpy_s(buffer_, size_, p);
	}
	m_Size_ = newSize;
	newBuffer[m_Size_] = '\0';

	delete[] m_Buffer_;
	m_Buffer_ = newBuffer;
}

		delete[] buffer_;
		buffer_ = newBuffer;
	}

	void TString::operator+=(const char* p)
	{
		size_t newSize = strlen(p) + this->Length() - 1;
		char* newBuffer = new char[newSize];
		for (size_t i = 0; i < this->Length(); i++)
		{
			newBuffer[i] = buffer_[i];
		}
		size_t count = this->Length() - 1;
		size_t counter = 0;
		while (*p)
		{
			newBuffer[counter + count] = *p;
			counter++;
			p++;
		}
		size_ = newSize;
		newBuffer[size_] = '\0';

		delete[] buffer_;
		buffer_ = newBuffer;
	}

	bool operator==(const TString &lhs, const TString &rhs)
	{
		if (lhs.Length() != rhs.Length())
		{
			if (lhs.m_Buffer_[i] != rhs.m_Buffer_[i])
			{
				if (lhs.buffer_[i] != rhs.buffer_[i])
				{
					return false;
				}
			}
		}
		return true;
	}

bool operator==(const TString &lhs, const char* rhs)
{
	return strcmp(lhs.m_Buffer_, rhs) == 0 ? true : false;
}

std::ostream & operator<<(std::ostream & os, const TString & str)
{
	os << str.m_Buffer_;
	return os;
}

TString::~TString()
{
 	delete[] m_Buffer_;
}


