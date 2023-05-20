#pragma once
#include "LibraryEntity.hpp"
#include "PeriodicityEnum.hpp"


class Periodical : public LibraryEntity {
public:
	Periodical(const char* title, PeriodicityEnum periodicity, const char* description, int edition, int publicationId, int publishedYear);

	PeriodicityEnum getPeriodicity() const;
	int getEdition() const;

	void setPeriodicity(PeriodicityEnum periodicity);
	void setEdition(int edition);
private:
	PeriodicityEnum periodicity;
	int edition;
};