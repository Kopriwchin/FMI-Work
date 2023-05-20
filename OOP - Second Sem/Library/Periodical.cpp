#include "Periodical.hpp"

Periodical::Periodical(const char* title, PeriodicityEnum periodicity, const char* description, int edition, int publicationId, int publishedYear) : LibraryEntity(title, description, publicationId, publishedYear)
{
	setPeriodicity(periodicity);
	setEdition(edition);
}

PeriodicityEnum Periodical::getPeriodicity() const {
	return this->periodicity;
}

int Periodical::getEdition() const {
	return this->edition;
}

void Periodical::setPeriodicity(PeriodicityEnum periodicity)
{
	this->periodicity = periodicity;
}

void Periodical::setEdition(int edition)
{
	this->edition = edition;
}
