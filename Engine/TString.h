#pragma once
#include <iostream>
namespace Engine
{
	class TString
	{ 
	public:
		TString();
		TString(const TString&);
		TString(const char *);

		char& operator[](unsigned int);

		void operator = (const TString&);
		void operator = (const char *);
		void operator += (const TString&);
		void operator += (const char *);

		friend bool operator==(const TString &lhs, const TString &rhs);
		friend bool operator==(const TString &lhs, const char * rhs);
		friend std::ostream& operator<<(std::ostream & os, const TString & str);

		inline char * GetBuffer() { return buffer_; }
		inline size_t Length() const { return size_; }

		~TString();

	private:
		size_t size_;
		char* buffer_;
	};
}
