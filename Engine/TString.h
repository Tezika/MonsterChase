#pragma once
#include <iostream>
class TString
{
public:
	TString();
	TString(const TString&);
	TString(const char *);

	unsigned int Length() const;
	char& operator[](unsigned int);

	void operator = (const TString&);
	void operator = (const char*);
	void operator += (const TString&);
	void operator += (const char*);

	friend bool operator==(const TString &lhs, const TString &rhs);
	friend bool operator==(const TString &lhs, const char* rhs);
	friend std::ostream& operator<<(std::ostream & os, const TString & str);
	                   
	inline char* GetBuffer() { return buffer_; }

	~TString();

private:
	unsigned int size_;
	char* buffer_;
};
