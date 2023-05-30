#pragma once

#include "LibraryEntity.hpp"
#include "User.hpp"

class Library {
public:
	Library() = default;
	Library(const Library&) = delete;
	Library& operator=(const Library&) = delete;
	~Library() = default;

	bool addPrint(const LibraryEntity& entity);
	bool removePrint(int publicationId) const;
	void printLibraryInfo();
	bool addUser(const User& user);
	bool removeUser(const char* username);
	void printPostponedPrints();
	void printUsersWithBorrowedPrint();
	void printAllUsersByReadBooks();
	bool borrowPrintFromUser(int publicationId);
	bool returnPrintToUser(int publicationId);

protected:
	unsigned libraryId = -1;
};