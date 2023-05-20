#pragma once
#include "LibraryEntity.hpp"

class Book : public LibraryEntity {
public:
	Book(const char* autor, const char* title, const char* publisher, short genre, const char* description, int publicationId, int publishedYear);

	void setAutor(const char* autor);
	void setPublisher(const char* publisher);
	void setGenre(short genre);

	const String& getAutor() const;
	const String& getPublisher() const;
	short getGenre() const;

private:
	String autor;
	String publisher;
	short genre;
};