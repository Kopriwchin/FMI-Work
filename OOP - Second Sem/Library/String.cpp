#include "String.hpp"
#pragma warning(disable:4996);

String::String()
{
	data = new char[1];
	data[0] = '\0';
	size = 0;
}

String::String(const char* input)
{
	int length = strlen(input);
	data = new char[length + 1];
	strcpy(data, input);
	size = length;
}

String::String(const String& other)
{
	data = new char[other.getLength() + 1];
	strcpy(data, other.data);
	size = other.getLength();
}

String& String::operator=(const String& other)
{
	if (this != &other)
	{
		delete[] data;
		data = new char[other.getLength() + 1];
		strcpy(data, other.data);
		size = other.getLength();
	}

	return *this;
}

String::~String()
{
	delete[] data;
	size = 0;
}

size_t String::getLength() const
{
	return size;
}

String& String::operator+=(const String& other)
{
	int length = this->size + other.getLength();
	char* result = new char[length + 1];
	
	strcpy(result, data);
	strcat(result, other.data);

	delete[] data;
	data = result;
	size = length;

	return *this;
}

char& String::operator[](size_t index)
{
	return data[index];
}

char String::operator[](size_t index) const
{
	return data[index];
}

const char* String::c_str() const {
	return data;
}

std::ostream& operator<<(std::ostream& os, const String& str)
{
	return os << str.data;
}
