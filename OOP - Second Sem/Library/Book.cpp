#include "Book.hpp"

Book::Book(const char* autor, const char* title, const char* publisher, short genre, const char* description, int publicationId, int publishedYear) : LibraryEntity(title, description, publicationId, publishedYear) {
	setAutor(autor);
	setPublisher(publisher);
	setGenre(genre);
}

void Book::setAutor(const char* autor) {
	this->autor = String(autor);
}

void Book::setPublisher(const char* publisher) {
	this->publisher = String(publisher);
}

void Book::setGenre(short genre) {
	if (genre < -1)
	{
		return;
	}
	this->genre = genre;
}

const String& Book::getAutor() const {
	return this->autor;
}

const String& Book::getPublisher() const {
	return this->publisher;
}

short Book::getGenre() const {
	return this->genre;
}