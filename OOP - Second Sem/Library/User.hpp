#pragma once

#include "String.hpp"
#include "UserPrintStatusEnum.hpp"

class User {
private:
    String name;
    int readBooksCount;
    int borrowedBooksCount;

    int* readBooksIds;
    int* borrowedBooksIds;

public:
    User() = default;
    User(const char* name, int readBooksCount, int* readBooksIds);

    void setName(const char* name);

    void setReadBooksCount(int booksCount);

    const String& getName() const;

    int getReadBooksCount() const;

    bool operator==(const User& other);
    bool operator!=(const User& other);
    bool operator<(const User& other);
    bool operator<=(const User& other);
    bool operator>(const User& other);
    bool operator>=(const User& other);
    UserPrintStatus operator[](int publicationId);
    bool operator+(int publicationId);
    bool operator+=(const User& other);
    bool operator-(const User& other);
    bool operator-=(const User& other);
};