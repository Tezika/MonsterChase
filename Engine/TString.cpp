#include "stdafx.h"
#include "TString.h"

TString::TString()
{
	buffer_ = nullptr;
	size_ = 0;
}

TString::TString(const TString& str)
{
	size_ = str.size_;
	buffer_ = new char[size_];
	strcpy_s(buffer_, size_, str.buffer_);
}

TString::TString(const char* p)
{
	size_ = strlen(p) + 1;
	buffer_ = new char[size_];
	strcpy_s(buffer_, size_, p);
}

unsigned int TString::Length() const
{
	if (buffer_ == nullptr)
	{
		return 0;
	}
	else
	{
		return size_;
	}
}

char& TString::operator[](unsigned int len)
{
	return buffer_[len];
}

void TString::operator=(const TString& str)
{
	size_ = str.size_;
	strcpy_s(buffer_, size_, str.buffer_);
}

void TString::operator=(const char* p)
{
	size_ = strlen(p) + 1;
	buffer_ = new char[size_];
	strcpy_s(buffer_, size_, p);
}

void TString::operator+=(const TString& str)
{
	auto newSize = str.Length() + this->Length();
	char* newBuffer = new char[newSize];
	for (size_t i = 0; i < str.Length()- 1; i++)
	{
		newBuffer[i] = buffer_[i];
	}
	size_t count = str.Length() - 1;
	for (size_t j = 0; j < str.Length(); j++)
	{
		newBuffer[j + count] = str.buffer_[j];
	}

	newBuffer[newSize] = '\0';
	size_ = newSize;

	delete[] buffer_;
	buffer_ = newBuffer;
}

void TString::operator+=(const char* p)
{
	 
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
			if (lhs.buffer_[i] != rhs.buffer_[i])
			{
				return false;
			}
		}
	}
	return true;
}

std::ostream & operator<<(std::ostream & os, const TString & str)
{
	os << str.buffer_;
	return os;
}


TString::~TString()
{
 	delete[] buffer_;
}

