#pragma once
#include "LibraryEntity.hpp"
#include "PeriodicityEnum.hpp"
#include "Comics.hpp"

class Comics : public LibraryEntity {
public:
	Comics(const char* autor, const char* title, const char* publisher, short genre, const char* description, PeriodicityEnum periodicity, int edition, int publicationId, int publishedYear);

	void setAutor(const char* autor);
	void setPublisher(const char* publisher);
	void setGenre(short genre);
	void setPeriodicity(PeriodicityEnum periodicity);
	void setEdition(int edition);

	const String& getAutor() const;
	const String& getPublisher() const;
	short getGenre() const;
	PeriodicityEnum getPeriodicity() const;
	int getEdition() const;

private:
	String autor;
	String publisher;
	short genre;
	PeriodicityEnum periodicity;
	int edition;
};