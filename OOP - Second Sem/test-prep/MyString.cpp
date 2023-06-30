#include "MyString.hpp"

MyString::MyString()
{
	length = 0;
	data = new char[1];
	data[0] = '\0';
}

MyString::MyString(const char* data)
{
	length = strlen(data);
	this->data = new char[length + 1];
	strcpy(this->data, data);
}

MyString::MyString(const MyString& other)
{
	copyFrom(other);
}

MyString& MyString::operator=(const MyString& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}


void MyString::free()
{
	delete[] data;
	data = nullptr;
}

MyString::~MyString()
{
	free();
}

size_t MyString::getLength() const
{
	return length;
}

void MyString::copyFrom(const MyString& other)
{
	length = other.length;
	data = new char[length + 1];
	strcpy(data, other.data);
}

const char* MyString::c_str() const
{
	return data;
}

std::ostream& operator<<(std::ostream& os, const MyString& str)
{
	return os << str.c_str();
}