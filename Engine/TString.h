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
	friend std::ostream& operator<<(std::ostream & os, const TString & str);

	~TString();
	
private:
	unsigned int size_;
	char* buffer_;
};

