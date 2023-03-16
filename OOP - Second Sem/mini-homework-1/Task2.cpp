/*
	A monthly calendar has 12 months.

	Make a structure 'Calendar' that will have a month (enum)
	and a year (pick a fitting type).
	
	Make a function that prints a calendar's month and year.
	
	Make functions that take a calendar and print the next and previous month and/or year
	(Make use of the previous function).

	Make functions that save and load a calendar to a text file in the format:
	{year} {month}
	where both 'year' and 'month' are integer values.
	// Note: This hasn't been covered in class yet,
	// but you can do some research about the library 'fstream'
	// as it is what we will be using going forward :)
*/

#include <iostream>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;

const char FILE_NAME[] = "output.txt";
const char INVALID_CALENDAR_DATA_MSG[]  = "Invalid calendar data!";
const char INVALID_FILE_MSG[] = "Error! Could not open file!";
const short BUFFER_SIZE = 1024;

enum MonthlyCalendar {
	Unknown = -1,
	January,
	February,
	March,
	April,
	May,
	June,
	July,
	August,
	September,
	October,
	November,
	December
};

struct Calendar {
	MonthlyCalendar month;
	short year;
};

const char* GetMonthName(int monthIndex) {
	if (monthIndex == 12)
	{
		monthIndex = 0;
	}
	else if (monthIndex == -1) {
		monthIndex = 11;
	}

	switch (monthIndex)
	{
		case January:
			return "January";
		case February:
			return "February";
		case March:
			return "March";
		case April:
			return "April";
		case May:
			return "May";
		case June:
			return "June";
		case July:
			return "July";
		case August:
			return "August";
		case September:
			return "September";
		case October:
			return "October";
		case November:
			return "November";
		case December:
			return "December";
		default:
			return "Unknown";
	}
}

void CheckForValidData (Calendar &calendar) {
	if (calendar.month < 0 || calendar.month > 11 || calendar.year < 0) {
		cout << INVALID_CALENDAR_DATA_MSG << endl;
		exit(-1);
	}
}

void PrintCalendarData(Calendar &calendar, bool fromMain = true) {
	if (fromMain)
	{
		CheckForValidData(calendar);
	}

	cout << GetMonthName(calendar.month) << ", " << calendar.year << endl;
}

void PrintNextAndPreviousYear(Calendar calendar) {
	CheckForValidData(calendar);

	cout << "Calendar's next year: " << endl;
	calendar.year += 1;
	PrintCalendarData(calendar, false);

	cout << "Calendar's previous year: " << endl;
	calendar.year -= 2;
	PrintCalendarData(calendar, false);
}

void PrintNextAndPreviousMonth(Calendar& calendar) {
	CheckForValidData(calendar);

	if (calendar.month + 1 > 11)
	{
		cout << "Calendar's previous month was November" << endl;
		cout << "Calendar's next month is January" << endl;
	}
	else if (calendar.month - 1 < 0) {
		cout << "Calendar's previous month was December" << endl;
		cout << "Calendar's next month is February" << endl;
	}
	else {
		cout << "Calendar's previous month was " << GetMonthName(calendar.month - 1) << endl;
		cout << "Calendar's next month is " << GetMonthName(calendar.month + 1) << endl;
	}
}

void SaveAndLoadCalendarData(Calendar& calendar, const char fileName[]) {
	std::ofstream file(fileName, std::ios::app);

	if (!file || !file.is_open())
	{
		cout << INVALID_FILE_MSG << endl;
		exit(-1);
	}

	file << '{' << calendar.year << "} " << '{' << GetMonthName(calendar.month) << '}' << endl;

	file.close();
}

int main() {
	Calendar calendar = { May, 2005 };
	Calendar secondCalendar = { June, 2003 };

	PrintCalendarData(calendar);
	PrintNextAndPreviousYear(calendar);
	PrintNextAndPreviousMonth(calendar);
	SaveAndLoadCalendarData(secondCalendar, FILE_NAME);
}