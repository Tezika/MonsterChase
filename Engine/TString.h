#pragma once
#include <iostream>
class TString
{
public:
	TString();
	TString(const TString&);
	TString(const char *);

	size_t Length() const;
	char& operator[](unsigned int);

	void operator = (const TString&);
	void operator = (const char*);
	void operator += (const TString&);
	void operator += (const char*);

	friend bool operator==(const TString &lhs, const TString &rhs);
	friend bool operator==(const TString &lhs, const char* rhs);
	friend std::ostream& operator<<(std::ostream & os, const TString & str);
	                   
	inline char* GetBuffer() { return m_Buffer_; }

	~TString();

private:
	size_t m_Size_;
	char* m_Buffer_;
};
