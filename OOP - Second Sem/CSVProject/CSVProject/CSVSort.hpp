#pragma once

#include "CSVDataType.hpp"
#include "CSVReader.hpp"

class CSVSort
{
public:
    void printWrongUsageOfMethod(int columnIndex, const string& dataType)
    {
        cout << "Data in the column at index " << columnIndex << " is not of type " << dataType << '!' << endl;
        cout << CHECK_GETTYPE_METHOD_MSG << endl << endl;;
    }

    bool compareFacultyNumbers(const string& num1, const string& num2)
    {
        if (num1.substr(2, 2) != num2.substr(2, 2)) {
            return num1.substr(2, 2) < num2.substr(2, 2);
        }

        return num1.substr(3, 7) > num2.substr(3, 7);
    }

    int sToI(const string& str)
    {
        int result = 0;
        int multiplier = 1;

        short cycles = str.size();

        for (size_t i = 0; i < cycles - 1; ++i)
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

    void sortText(int columnIndex, bool ascending = true)
    {
        if (inferDataType(data[0][columnIndex]) != DataType::String)
        {
            printWrongUsageOfMethod(columnIndex, "string");
            return;
        }

        int columnsCount = data.size();

        bool swappedFlag = false;

        if (ascending)
        {
            for (size_t i = 0; i < columnsCount - 1; ++i)
            {
                for (size_t j = 0; j < columnsCount - i - 1; j++)
                {
                    if (data[j][columnIndex] > data[j + 1][columnIndex])
                    {
                        std::swap(data[j], data[j + 1]);
                        swappedFlag = true;
                    }
                }
                if (swappedFlag == false)
                {
                    return;
                }
                swappedFlag = false;
            }
        }
        else
        {
            for (size_t i = 0; i < columnsCount - 1; ++i)
            {
                for (size_t j = 0; j < columnsCount - i - 1; j++)
                {
                    if (data[j][columnIndex] < data[j + 1][columnIndex])
                    {
                        std::swap(data[j], data[j + 1]);
                        swappedFlag = true;
                    }
                }
                if (swappedFlag == false)
                {
                    return;
                }
                swappedFlag = false;
            }
        }
    }

    void sortFacultyNumbers(int columnIndex, bool ascending = true)
    {
        if (inferDataType(data[0][columnIndex]) != DataType::FacultyNumber)
        {
            printWrongUsageOfMethod(columnIndex, "faculty number");
            return;
        }

        int columnsCount = data.size();

        bool swappedFlag = false;

        if (ascending) {
            for (size_t i = 0; i < columnsCount - 1; ++i) {
                for (size_t j = 0; j < columnsCount - i - 1; ++j) {
                    if (compareFacultyNumbers(data[j][columnIndex], data[j + 1][columnIndex]))
                    {
                        std::swap(data[j], data[j + 1]);
                        swappedFlag = true;
                    }
                }
                if (swappedFlag == false)
                {
                    return;
                }
                swappedFlag = false;
            }
        }
        else {
            for (size_t i = 0; i < columnsCount - 1; ++i) {
                for (size_t j = 0; j < columnsCount - i - 1; ++j) {
                    if (!compareFacultyNumbers(data[j][columnIndex], data[j + 1][columnIndex]))
                    {
                        std::swap(data[j], data[j + 1]);
                        swappedFlag = true;
                    }
                }
                if (swappedFlag == false)
                {
                    return;
                }
                swappedFlag = false;
            }
        }
    }

    void sortNumbers(int columnIndex, bool ascending = true)
    {
        if (inferDataType(data[0][columnIndex]) != DataType::Number)
        {
            printWrongUsageOfMethod(columnIndex, "number");
            return;
        }

        size_t columnsCount = data.size();

        bool swappedFlag = false;

        if (ascending)
        {
            for (size_t i = 0; i < columnsCount - 1; ++i)
            {
                for (size_t j = 0; j < columnsCount - i - 1; j++)
                {
                    if (sToI(data[j][columnIndex]) > sToI(data[j + 1][columnIndex]))
                    {
                        std::swap(data[j], data[j + 1]);
                        swappedFlag = true;
                    }
                }
                if (swappedFlag == false)
                {
                    return;
                }
                swappedFlag = false;
            }
        }
        else
        {
            for (size_t i = 0; i < columnsCount - 1; ++i)
            {
                for (size_t j = 0; j < columnsCount - i - 1; j++)
                {
                    if (sToI(data[j][columnIndex]) < sToI(data[j + 1][columnIndex]))
                    {
                        std::swap(data[j], data[j + 1]);
                        swappedFlag = true;
                    }
                }
                if (swappedFlag == false)
                {
                    return;
                }
                swappedFlag = false;
            }
        }
    }

    void sortDate(int columnIndex, bool ascending = true)
    {
        if (inferDataType(data[0][columnIndex]) != DataType::DateTime)
        {
            printWrongUsageOfMethod(columnIndex, "date");
            return;
        }

        int columnsCount = data.size();

        bool swappedFlag = false;

        if (ascending)
        {
            for (size_t i = 0; i < columnsCount - 1; ++i)
            {
                for (size_t j = 0; j < columnsCount - i - 1; j++)
                {
                    if (strcmp(data[j][columnIndex].c_str(), data[j + 1][columnIndex].c_str()) == 1)
                    {
                        std::swap(data[j], data[j + 1]);
                        swappedFlag = true;
                    }
                }
                if (swappedFlag == false)
                {
                    return;
                }
                swappedFlag = false;
            }
        }
        else
        {
            for (size_t i = 0; i < columnsCount - 1; ++i)
            {
                for (size_t j = 0; j < columnsCount - i - 1; j++)
                {
                    if (strcmp(data[j][columnIndex].c_str(), data[j + 1][columnIndex].c_str()) == -1)
                    {
                        std::swap(data[j], data[j + 1]);
                        swappedFlag = true;
                    }
                }
                if (swappedFlag == false)
                {
                    return;
                }
                swappedFlag = false;
            }
        }
    }

    void sortColumn(int index, bool ascending = true)
    {
        int columnsCount = data.size();

        if (index >= columnsCount || columnsCount < 0)
        {
            cout << "Invalid index!" << endl;
            return;
        }

        DataType columnType = getDataTypeOfColumn(index);

        switch (columnType)
        {
        case DataType::String:
            sortText(index, ascending);
            break;
        case DataType::Number:
            sortNumbers(index, ascending);
            break;
        case DataType::DateTime:
            sortDate(index, ascending);
            break;
        case DataType::FacultyNumber:
            sortFacultyNumbers(index, ascending);
            break;
        };
    }

    void sortColumn(const string& name, bool ascending = true)
    {
        for (size_t i = 0; i < columnNames.size(); ++i)
        {
            if (columnNames[i] == name)
            {
                sortColumn(i, ascending);
                return;
            }
        }

        cout << "No column with such name was found!" << endl;
    }
};