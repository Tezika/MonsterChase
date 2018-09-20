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
	size_t newSize = str.Length() + this->Length() - 1;
	char* newBuffer = new char[newSize];
	for (size_t i = 0; i < this->Length(); i++)
	{
		newBuffer[i] = buffer_[i];
	}
	size_t count = this->Length() - 1;
	for (size_t j = 0; j < str.Length(); j++)
	{
		newBuffer[j + count] = str.buffer_[j];
	}
	size_ = newSize;
	newBuffer[size_] = '\0';

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

