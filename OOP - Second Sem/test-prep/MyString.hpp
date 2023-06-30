#pragma once
#pragma warning (disable:4996)

#include <iostream>

class MyString
{
	char* data;
	size_t length;

	void copyFrom(const MyString& data);
	void free();
public:
	MyString();
	MyString(const char* data);
	MyString(const MyString& other);
	MyString& operator=(const MyString& other);
	~MyString();

	size_t getLength() const;
	const char* c_str() const;
};

std::ostream& operator<<(std::ostream& os, const MyString& str);