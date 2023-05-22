#include "User.hpp"

User::User(const char* name, int readBooksCount, int* readBooksIds)
{
    setName(name);
    setReadBooksCount(readBooksCount);
    //this->readBooksIds = new int[4];
}

void User::setName(const char* name)
{
    this->name = String(name);
}

void User::setReadBooksCount(int booksCount)
{
    if (booksCount < 0)
    {
        return;
    }

    this->readBooksCount = booksCount;
}

/*void setReadBooksIds(int* readBooksIds) {
        if (readBooksIds == nullptr)
            return;

        if (this->readBooksIds != nullptr)
            delete[] this->readBooksIds;
 }*/

const String& User::getName() const
{
    return name;
}

int User::getReadBooksCount() const
{
    return readBooksCount;
}

/*int* getReadBooksIds() const {
        return readBooksIds;
}*/

bool User::operator==(const User& other) {
    return strcmp(name.c_str(), other.name.c_str()) == 0;
}

bool User::operator!=(const User& other) {
    return !(this == &other); 
}

bool User::operator<(const User& other) {
    return this->readBooksCount < other.readBooksCount;
}

bool User::operator<=(const User& other) {
    return this->readBooksCount < other.readBooksCount || this->readBooksCount == other.readBooksCount;
}

bool User::operator>(const User& other) {
    return !(this <= &other);
}

bool User::operator>=(const User& other) {
    return !(this < &other);
}

UserPrintStatus User::operator[](int publicationId) {
    for (size_t i = 0; i < borrowedBooksCount; i++)
    {
        if (borrowedBooksIds[i] == publicationId)
        {
            return UserPrintStatus::Currently_Reading;
        }
    }

    for (size_t i = 0; i < readBooksCount; i++)
    {
        if (readBooksIds[i] == publicationId)
        {
            return UserPrintStatus::Already_Read;
        }
    }

    return UserPrintStatus::Never_Taken;
}

bool User::operator+(int publicationId) {
    return false;
}

