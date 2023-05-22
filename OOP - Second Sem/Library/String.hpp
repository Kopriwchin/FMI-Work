#pragma once

#include <cstring>
#include <ostream>

class String {
private:
	char* data;
	size_t size;

public:
	String();
	String(const char* input);
	String(const String& other);
	String& operator=(const String& other);
	~String();

	const char* c_str() const;
	size_t getLength() const;
	String& operator+=(const String& other);

	char& operator[](size_t index);
	char operator[](size_t index) const;
	friend std::ostream& operator<<(std::ostream& os, const String& str);
};