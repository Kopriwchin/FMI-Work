#pragma warning(disable:4996)
#include "LibraryEntity.hpp"
#include <iostream>

LibraryEntity::LibraryEntity(const char* title, const char* description, int publicationId, short publishedYear) {
    setTitle(title);
    setDescription(description);
    setPublicationid(publicationId);
    setPublishedYear(publishedYear);
}

//LibraryEntity::LibraryEntity(const LibraryEntity& other)
//    : genre(other.genre), publicationId(other.publicationId), publishedYear(other.publishedYear) {
//    autor = new char[strlen(other.autor) + 1];
//    title = new char[strlen(other.title) + 1];
//    publisher = new char[strlen(other.publisher) + 1];
//    description = new char[strlen(other.description) + 1];
//
//    strcpy(autor, other.autor);
//    strcpy(title, other.title);
//    strcpy(publisher, other.publisher);
//    strcpy(description, other.description);
//}
//
//LibraryEntity::~LibraryEntity()
//{
//    delete[] autor;
//    delete[] title;
//    delete[] publisher;
//    delete[] description;
//
//    genre = -1;
//    publicationId = -1;
//    publishedYear = -1;
//}

LibraryEntity::~LibraryEntity() {};

const String& LibraryEntity::getTitle() const
{
	return title;
}

const String& LibraryEntity::getDescription() const
{
	return description;
}

int LibraryEntity::getPublicationId() const
{
	return publicationId;
}

short LibraryEntity::getPublishedYear() const
{
	return publishedYear;
}

void LibraryEntity::setTitle(const char* title)
{
    this->title = String(title);
}

void LibraryEntity::setDescription(const char* description)
{
    if (strlen(description) < 1)
    {
        return;
    }
    this->description = String(description);
}

void LibraryEntity::setPublicationid(int publicationId)
{
    // Setting to invalid value so it can be processed later
    if (publicationId < -1)
    {
        this->publicationId = -1;
        return;
    }

    this->publicationId = publicationId;
}

void LibraryEntity::setPublishedYear(short publishedYear)
{
    // Setting to invalid value so it can be processed later
    if (publishedYear <= 0)
    {
        this->publishedYear = -1;
        return;
    }

    this->publishedYear = publishedYear;
}