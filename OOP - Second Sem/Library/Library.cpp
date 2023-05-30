#include <iostream>
#include <fstream>

#include "Book.hpp"
#include "Comics.hpp"
#include "Constants.hpp"
#include "Library.hpp"
#include "Periodical.hpp"

using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

bool Library::addPrint(const LibraryEntity& entity)
{
	ofstream allPrintsFile(LIBRARY_PRINTS_FILE, std::ios::binary | std::ios::app);

	if (!allPrintsFile || !allPrintsFile.is_open())
	{
		cout << ERROR_WRITING_FILE_MSG << endl;
		return false;
	}

	entity.writeToFile(allPrintsFile);
	return true;
}

bool Library::removePrint(int publicationId) const
{
	ifstream readFile(LIBRARY_PRINTS_FILE, std::ios::binary);

	if (!isReadFileValid(readFile))
	{
		return false;
	}

	ofstream writeFile(INIT_FILE_NAME, std::ios::binary);

	if (!isWriteFileValid(writeFile))
	{
		return false;
	}

	while (!readFile.eof())
	{
		int printType;
		readFile.read(reinterpret_cast<char*>(&printType), sizeof(int));

		switch (printType)
		{
			case 0:
			{
				Book book = Book::readFromFile(readFile);
				if (book.getPublicationId() == publicationId)
				{
					writeFile.seekp(readFile.tellg(), std::ios::beg);
					const int bufferSize = 1024;
					char buffer[bufferSize];

					while (!readFile.eof()) {
						readFile.read(buffer, bufferSize);
						std::streamsize bytesRead = readFile.gcount();

						writeFile.write(buffer, bytesRead);
					}
					return true;
				}
				else
				{
					book.writeToFile(writeFile);
				}
				break;
			}
				
			case 1:
			{
				Periodical periodical = Periodical::readFromFile(readFile);
				if (periodical.getPublicationId() == publicationId)
				{
					writeFile.seekp(readFile.tellg(), std::ios::beg);
					const int bufferSize = 1024;
					char buffer[bufferSize];

					while (!readFile.eof()) {
						readFile.read(buffer, bufferSize);
						std::streamsize bytesRead = readFile.gcount();

						writeFile.write(buffer, bytesRead);
					}
					return true;
				}
				else
				{
					periodical.writeToFile(writeFile);
				}
				break;
			}
			case 2:
			{
				Comics comics = Comics::readFromFile(readFile);
				if (comics.getPublicationId() == publicationId)
				{
					writeFile.seekp(readFile.tellg(), std::ios::beg);
					const int bufferSize = 1024;
					char buffer[bufferSize];

					while (!readFile.eof()) {
						readFile.read(buffer, bufferSize);
						std::streamsize bytesRead = readFile.gcount();

						writeFile.write(buffer, bytesRead);
					}
					return true;
				}
				else
				{
					comics.writeToFile(writeFile);
				}
				break;
			}
			default:
				break;
		}

	}

	// Delete "initFile.dat" file and renaming the initial file to "all_prints.dat"
	readFile.close();
	writeFile.close();

	if (remove(LIBRARY_PRINTS_FILE)) {
		cout << "\t\tError deleting " << LIBRARY_PRINTS_FILE << " file!" << endl;
		return true;
	}

	if (std::rename(INIT_FILE_NAME, LIBRARY_PRINTS_FILE)) {
		cout << "\t\tError renaming " << INIT_FILE_NAME << " to " << LIBRARY_PRINTS_FILE << endl;
		return true;
	}

	return true;
}

//bool Library::removePrintEdition(int publicationId)
//{
//	ifstream readFile(LIBRARY_PRINTS_FILE);
//
//	if (!isReadFileValid(readFile))
//	{
//		return false;
//	}
//
//	int a, b;
//	while (readFile >> a >> b)
//	{
//		if (a == publicationId)
//		{
//			if (b == 1) removeBook(publicationId);
//			//else if (b == 2) { RemovePeriodical(publicationId) };
//			//else if (b == 3) { RemoveComics(publicationId) };
//		}
//	}
//
//	return false;
//}

void Library::printLibraryInfo()
{
	std::ifstream readFile(LIBRARY_PRINTS_FILE);

	if (!readFile || !readFile.is_open())
	{
		cout << ERROR_READING_FILE_MSG << endl;
		return;
	}

	LibraryEntity** entities = { nullptr };

	int classType;

	readFile.read(reinterpret_cast<char*>(&classType), sizeof(int));

	// 0 for book, 1 for periodical, 2 for comics
	switch (classType)
	{
		case 0:
		{
			Book book = Book::readFromFile(readFile);
			// add to entities
			break;
		}
		case 1:
		{
			Periodical periodical = Periodical::readFromFile(readFile);
			break;
		}
		case 2:
		{
			Comics comics = Comics::readFromFile(readFile);
			break;
		}
		default:
			break;
	}

	// TODO: da gi drupna wsichkite w edin masiw i da gi sortiram tuk.
}

bool Library::addUser(const User& user)
{
	ofstream writeFile(ALL_USERS_FILE, std::ios::binary | std::ios::app);

	if (!writeFile || !writeFile.is_open())
	{
		cout << ERROR_WRITING_FILE_MSG << endl;
		return false;
	}

	

	//writeFile.write((char*)user, sizeof(User))
	return true;
}

bool Library::removeUser(const char* username)
{
	return false;
}

void Library::printPostponedPrints()
{
}

void Library::printUsersWithBorrowedPrint()
{
}

void Library::printAllUsersByReadBooks()
{
}

bool Library::borrowPrintFromUser(int publicationId)
{
	return false;
}

bool Library::returnPrintToUser(int publicationId)
{
	return false;
}