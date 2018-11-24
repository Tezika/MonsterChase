#pragma once
#include <iostream>
namespace Engine
{
	class TString
	{
	public:
		TString();
		TString(const TString &);
		TString(const char *);
		~TString();

		char& operator[](unsigned int);

		void operator = (const TString &);
		void operator = (const char *);
		void operator += (const TString &);
		void operator += (const char *);
		void SetBuffer(const char *);

		friend bool operator==(const TString &, const TString &);
		friend bool operator==(const TString &, const char *);
		friend std::ostream& operator<<(std::ostream &, const TString &);
		friend std::istream & operator>>(std::istream & is, TString & str);

		inline char* GetBuffer() { return m_buffer; }
		inline size_t Length() const { return m_size; }

	private:
		size_t m_size;
		char * m_buffer;
	};

};
