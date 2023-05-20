#pragma once
#include "String.hpp"

class LibraryEntity {
public:
    LibraryEntity() = delete;
    LibraryEntity(const char* title, const char* description, int publicationId, short publishedYear);

    virtual ~LibraryEntity() = 0;

    const String& getTitle() const;
    const String& getDescription() const;
    int getPublicationId() const;
    short getPublishedYear() const;

    void setTitle(const char* title);
    void setDescription(const char* description);
    void setPublicationid(int publicationId);
    void setPublishedYear(short publishedYear);

private:
    String title;
    String description;
    int publicationId;
    short publishedYear;
};