#include "Comics.hpp"

Comics::Comics(const char* autor, const char* title, const char* publisher, short genre, const char* description, PeriodicityEnum periodicity, int edition, int publicationId, int publishedYear) : LibraryEntity(title, description, publicationId, publishedYear) {
	setAutor(autor);
	setPublisher(publisher);
	setGenre(genre);
	setPeriodicity(periodicity);
	setEdition(edition);
}

void Comics::setAutor(const char* autor) {
	this->autor = String(autor);
}

void Comics::setPublisher(const char* publisher) {
	this->publisher = String(publisher);
}

void Comics::setGenre(short genre) {
	if (genre < -1)
	{
		return;
	}
	this->genre = genre;
}

void Comics::setPeriodicity(PeriodicityEnum periodicity) {
	this->periodicity = periodicity;
}

void Comics::setEdition(int edition) {
	this->edition = edition;
}

const String& Comics::getAutor() const {
	return this->autor;
}

const String& Comics::getPublisher() const {
	return this->publisher;
}

short Comics::getGenre() const {
	return this->genre;
}

PeriodicityEnum Comics::getPeriodicity() const {
	return this->periodicity;
}

int Comics::getEdition() const {
	return this->edition;
}