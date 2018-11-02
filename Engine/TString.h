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
		~TString();

		char& operator[](unsigned int);

		void operator = (const TString&);
		void operator = (const char *);
		void operator += (const TString&);
		void operator += (const char *);

		friend bool operator==(const TString &lhs, const TString &rhs);
		friend bool operator==(const TString &lhs, const char* rhs);
		friend std::ostream& operator<<(std::ostream & os, const TString & str);

		inline char* GetBuffer() { return m_Buffer_; }

		inline size_t Length() const { return m_Size_; }

	private:
		size_t m_Size_;
		char* m_Buffer_;
	};

};
