#pragma once

#include <iostream>
#include <string>

using std::string;

class Date {
private:
    int day;
    int month;
    int year;

    int sToI(const string& str)
    {
        int result = 0;
        int multiplier = 1;

        short cycles = str.size();

        for (int i = 0; i < cycles - 1; i++)
        {
            multiplier *= 10;
        }

        int index = 0;

        while (multiplier != 0)
        {
            result += (str[index] - '0') * multiplier;
            multiplier /= 10;
            index++;
        }

        return result;
    }

public:
    Date(int day, int month, int year) : day(day), month(month), year(year) {}

    bool isValid() {
        if (month < 1 || month > 12 || day < 1 || year < 1)
            return false;

        int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
            daysInMonth[1] = 29;

        return day <= daysInMonth[month - 1];
    }

    void parseFromString(const std::string& dateString) {
        // Assuming the date string is in the format "YYYY-MM-DD"
        size_t found = dateString.find('-');
        string yearStr = dateString.substr(0, found);

        size_t nextFound = dateString.find('-', found + 1);
        string monthStr = dateString.substr(found + 1, nextFound - found - 1);

        string dayStr = dateString.substr(nextFound + 1);

        year = sToI(yearStr);
        month = sToI(monthStr);
        day = sToI(dayStr);
    }

    string& getDate()
    {
        string result;
        result = day + '-' + month + '-' + year;

        return result;
    }


    void print() {
        std::cout << day << "-" << month << "-" << year << std::endl;
    }
};