#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <regex>
#include <iomanip>

#include "Date.hpp"
#include "Constants.hpp"

using std::ifstream;
using std::ofstream;

using std::string;
using std::stringstream;
using std::regex;
using std::vector;

using std::cout;
using std::cin;
using std::endl;

enum class DataType {
    Unknown = -1,
    String,
    Number,
    DateTime,
    FacultyNumber
};

bool isNumber(const string& value) {
    return std::regex_match(value, regex(R"(^-?\d*\.?\d+$)"));
}

bool isDateTime(const string& value) {
    if (std::regex_match(value, regex(R"(\d{4}-\d{2}-\d{2}$)")))
    {
        return Date::isValid(value);
    }

    return false;
}

bool isFacultyNumber(const string& value) {
    return std::regex_match(value, regex(R"(\dMI(0[1-9]|09)\d{5}\b)"));
}

class CSVParser
{
private:
    string filename;
    vector<string> columnNames;
    vector<DataType> columnDataTypes;
    vector<vector<string>> data;
    bool isModified = false;
public:
    CSVParser() {};
    CSVParser(const string& filename) : filename(filename) {};

#pragma region Properties
    const vector<vector<string>>& getData() const {
        return data;
    }

    const string getFilename() const
    {
        return filename;
    }

    bool getModifiedState() const {
        return isModified;
    }
#pragma endregion

#pragma region HeadCommands

    bool open(const string& filename, bool hasHeaderRow = true) {
        this->filename = filename;

        ifstream file(filename);

        if (!file.is_open()) {
            cout << "Failed to open the file: " << filename << endl;
            return false;
        }

        string line;
        string cell;
        
        if (hasHeaderRow)
        {
            std::getline(file, line);
            stringstream ss(line);

            while (std::getline(ss, cell, ',')) {
                columnNames.push_back(trim(cell));
            }
        }

        vector<string> row;

        while (std::getline(file, line)) {
            
            vector<string> row = parseCSVLine(line);

            size_t rowSize = row.size();

            if (row.size() != 0)
            {
                data.push_back(row);
            }

            row.clear();
        }

        file.close();

        validateColumnTypes();

        return true;
    }

    void save()
    {
        saveAs(filename);
    }

    void saveAs(string filenameInput)
    {
        ofstream file(filenameInput);

        if (!file || !file.is_open())
        {
            cout << INVALID_FILE_MSG << endl;
            return;
        }


        size_t rowsCount = data.size();
        size_t columnsCount = data[0].size();

        size_t columnNamesCount = columnNames.size();

        if (columnNamesCount > 0)
        {
            for (size_t i = 0; i < columnNamesCount - 1; i++)
            {
                file << columnNames[i] << ",";
            }
            file << columnNames[columnNamesCount - 1] << endl;
        }

        for (size_t i = 0; i < rowsCount; ++i)
        {
            vector<string> row = data[i];

            for (size_t j = 0; j < columnsCount - 1; j++)
            {
                file << row[j] << ",";
            }
            file << row[columnsCount - 1];
            file << endl;
        }
        file.close();

        isModified = false;
    }

    void exit()
    {
        if (isModified)
        {
            while (true)
            {
                cout << "There are some unsaved changes made to the CSV file." << endl;
                cout << "Do you want to save them before exiting?" << endl;
                cout << "Enter \"yes\" to save, \"no\" to exit" << endl;

                string command;
                cin >> command;

                if (command == "yes")
                {
                    save();
                    std::exit(0);
                }
                else if (command == "no")
                {
                    std::exit(0);
                }
                else {
                    cout << endl << "Invalid command!" << endl;
                }
            }
        }
    }

#pragma endregion

#pragma region Print

    void printHeaderRow() const
    {
        if (columnNames.empty())
            return;

        size_t columnsCount = columnNames.size();

        for (size_t i = 0; i < columnsCount; ++i)
        {
            cout << std::left << std::setw(20) << columnNames[i].c_str();
        }

        cout << endl;
    }

    void print(size_t rowsToPrint = 10) const
    {
        printHeaderRow();

        size_t rowsCount = data.size();

        if (rowsCount == 0)
        {
            cout << "No data to show!" << endl;
            return;
        }

        if (rowsToPrint < 0)
        {
            rowsToPrint *= -1;

            for (size_t i = rowsToPrint - 1; i >= 0; --i)
            {
                printRow(i);
            }
            cout << endl;
            return;
        }

        if (rowsToPrint > rowsCount)
        {
            rowsToPrint = rowsCount;
        }

        size_t columnsCount = data[0].size();

        for (size_t i = 0; i < rowsToPrint; ++i)
        {
            for (size_t j = 0; j < columnsCount; ++j)
                cout << std::left << std::setw(20) << data[i][j];
            //printRow(i);

            cout << endl;
        }

        cout << endl;
    }
    
    void printRow(size_t index) const
    {
        size_t rowsCount = data.size();
        size_t columnsCount = data[0].size();

        if (index >= rowsCount)
        {
            cout << "Invalid index!" << endl;
            return;
        }

        for (size_t i = 0; i < columnsCount; ++i)
            cout << std::left << std::setw(20) << data[index][i];

        cout << endl;
    }
    
    void printRow(const vector<string>& row) const
    {
        size_t size = row.size();

        for (size_t i = 0; i < size; ++i)
            cout << std::left << std::setw(20) << row[i].c_str();

        cout << endl;
    }

    void printColumn(size_t index) const
    {
        size_t rowsCount = data.size();

        if (index >= rowsCount)
        {
            cout << "Invalid index!" << endl;
            return;
        }

        for (size_t i = 0; i < rowsCount; ++i)
            cout << data[i][index] << endl;

        cout << endl;
    }

    void printColumn(const string& name) const
    {
        size_t columsCount = columnNames.size();

        for (size_t i = 0; i < columsCount; ++i)
        {
            if (columnNames[i] == name)
            {
                printColumn(i);
                return;
            }
        }

        cout << "No column with such name was found!" << endl;
    }

#pragma endregion

    void removeColumn(const string& name)
    {
        size_t columnsCount = columnNames.size();

        for (size_t i = 0; i < columnsCount; i++)
        {
            if (columnNames[i] == name)
            {
                removeColumn(i);
                return;
            }
        }

        cout << "No column with such name exists!" << endl;
    }

    void removeColumn(size_t index) {
        int columnsCount = data[0].size();

        if (index >= columnsCount)
        {
            cout << "Invalid index!" << endl << endl;
            return;
        }

        for (size_t i = 0; i < columnsCount; i++)
        {
            vector<string>& row = data[i];

            if (row.size() > index) {
                row.erase(row.begin() + index);
            }

            isModified = true;
        }

        if (!columnNames.empty())
        {
            columnNames.erase(columnNames.begin() + index);
        }
    }

    void changeColumnOrder(string& permutation) {

        if (data.empty())
        {
            cout << "No data is loaded!" << endl;
            return;
        }

        int numColumns = data[0].size();
        stringstream stringStr(trim(permutation));
        vector<int> newOrder;

        // Parse the permutation string and validate the column numbers
        string cell;
        while (std::getline(stringStr, cell, ' '))
        {
            int num = sToI(trim(cell));

            if (num < 1 || num > numColumns)
            {
                cout << "Invalid column number in the permutation: " << num << endl;
                return;
            }

            // Adjusting to zero-based indexing
            for (size_t i = 0; i < newOrder.size(); i++)
            {
                if (newOrder[i] == num - 1)
                {
                    cout << "Invalid permutation! Duplicate column numbers!" << endl;
                    return;
                }
            }

            newOrder.push_back(num - 1);
        }

        int newOrderCount = newOrder.size();

        if (newOrderCount != numColumns) {
            cout << "Invalid permutation: Missing column number." << endl;
            return;
        }

        vector<vector<string>> newData(data.size(), vector<string>(numColumns));
        vector<string> newColumnNames(numColumns);
        vector<DataType> newColumnDataTypes(numColumns);


        for (size_t i = 0; i < data.size(); i++) {
            for (size_t j = 0; j < newOrderCount; j++) {
                newData[i][j] = data[i][newOrder[j]];
            }
        }

        for (size_t i = 0; i < numColumns; i++)
        {
            newColumnNames[i] = columnNames[newOrder[i]];
            newColumnDataTypes[i] = columnDataTypes[newOrder[i]];
        }

        columnNames = newColumnNames;
        columnDataTypes = newColumnDataTypes;
        data = newData;
        isModified = true;
    }

    void addRowCopy(size_t index) {
        if (index >= data.size())
            cout << "Invalid row number." << endl;

        vector<string> newRow = data[index];
        data.push_back(newRow);

        isModified = true;
    }

    void addRowWithMinValues() {
        if (data.empty())
        {
            cout << "No data available." << endl;
            return;
        }

        vector<string> newRow;

        for (size_t i = 0; i < data[0].size(); ++i) {
            string minValue = data[0][i]; // Initialize the minimum value with the first element

            if (getDataTypeOfColumn(i) == DataType::Number)
            {
                for (size_t row = 1; row < data.size(); ++row) {
                    if (sToI(data[row][i]) < sToI(minValue)) {
                        minValue = data[row][i];
                    }
                }
            }
            else
            {
                for (size_t row = 1; row < data.size(); ++row) {
                    if (data[row][i] < minValue) {
                        minValue = data[row][i];
                    }
                }
            }

            newRow.push_back(minValue);
        }

        data.push_back(newRow);
        isModified = true;
    }

    void addRowWithMaxValues() {
        if (data.empty())
        {
            cout << "No data available." << endl;
            return;
        }

        vector<string> newRow;

        for (size_t i = 0; i < data[0].size(); ++i) {
            string maxValue = data[0][i];

            for (size_t row = 1; row < data.size(); ++row) {
                if (data[row][i] > maxValue) {
                    maxValue = data[row][i];
                }
            }

            newRow.push_back(maxValue); // Add the minimum value to the new row
        }

        data.push_back(newRow); // Add the new row to the end of the table
        isModified = true;
    }

    size_t getColumnIndex(const string& name) const
    {
        size_t columnsCount = columnNames.size();

        for (size_t i = 0; i < columnsCount; ++i)
        {
            if (columnNames[i] == name)
            {
                return i;
            }
        }

        return -1;
    }

    string dataTypeToStr(DataType type)
    {
        switch (type)
        {
        case DataType::String:
            return "String";
            break;
        case DataType::Number:
            return "Number";
            break;
        case DataType::DateTime:
            return "DateTime";
            break;
        case DataType::FacultyNumber:
            return "FacultyNumber";
            break;
        default:
            return "Unknown";
        }
    }

    DataType inferDataType(const string& value) {
        if (isNumber(value)) {
            return DataType::Number;
        }
        else if (isDateTime(value)) {
            return DataType::DateTime;
        }
        else if (isFacultyNumber(value)) {
            return DataType::FacultyNumber;
        }
        else if (value.empty())
        {
            return DataType::Unknown;
        }
        else {
            return DataType::String;
        }
    }

    DataType getDataTypeOfColumn(int columnIndex)
    {
        return columnDataTypes[columnIndex];
    }

    void sortColumn(int index, bool ascending = true)
    {
        size_t columnsCount = data.size();

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
        size_t columnNamesCount = columnNames.size();

        for (size_t i = 0; i < columnNamesCount; ++i)
        {
            {
                sortColumn(i, ascending);
                return;
            }
        }

        cout << "No column with such name was found!" << endl;
    }

    void filter(const string& columnName, const string& condition, const string& value)
    {
        int columnIndex = getColumnIndex(columnName);

        if (columnIndex == -1)
        {
            cout << "Invalid column name!" << endl;
            return;
        }

        filter(columnIndex, condition, value);
    }

    void filter(int columnIndex, const string& condition, const string& value)
    {
        if (columnIndex < 0 || columnIndex >= data[0].size()) {
            cout << "Invalid column index!" << endl;
            return;
        }

        vector<vector<string>> filteredRows;
        size_t rowsCount = data.size();

        for (size_t i = 0; i < rowsCount; i++)
        {
            const vector<string> row = data[i];
            const string& cellValue = row[columnIndex];

            bool matchesFilter = false;

            if (condition == "==") {
                matchesFilter = (cellValue == value);
            }
            else if (condition == "!=") {
                matchesFilter = (cellValue != value);
            }
            else if (condition == ">") {
                matchesFilter = (cellValue > value);
            }
            else if (condition == "<") {
                matchesFilter = (cellValue < value);
            }
            else if (condition == ">=") {
                matchesFilter = (cellValue >= value);
            }
            else if (condition == "<=") {
                matchesFilter = (cellValue <= value);
            }
            else {
                cout << "Invalid condition operator." << endl;
                return;
            }

            if (matchesFilter) {
                filteredRows.push_back(row);
            }
        }

        data = filteredRows;
        isModified = true;
    }
   
    void validateColumnTypes() {
        if (data.empty()) {
            cout << "No data loaded! Please load the CSV file first." << endl;
            std::exit(-1);
        }

        bool isValid = true;
        size_t columnsCount = data[0].size();
        columnDataTypes.reserve(columnsCount);

        for (size_t i = 0; i < columnsCount; ++i)
        {
            columnDataTypes.push_back(DataType::Unknown);
        }

        // Determine column data types
        size_t rowsCount = data.size();

        for (size_t i = 0; i < rowsCount; ++i)
        {
            vector<string>& row = data[i];

            for (size_t j = 0; j < columnsCount; ++j) {

                if (columnDataTypes[j] == DataType::Unknown) {
                    // First non-empty value encountered, determine its type
                    columnDataTypes[j] = inferDataType(row[j]);
                }
                else if (inferDataType(row[j]) != columnDataTypes[j]) {
                    // Type mismatch detected
                    // Calculate the position of the bad data
                    if (!columnNames.empty())
                    {
                        cout << "Invalid CSV file! Row " << i + 2 << " on column " << j + 1 << " does not match the intended type! " << "(expected " << dataTypeToStr(columnDataTypes[j]) << ')' << endl;
                    }
                    else
                    {
                        cout << "Invalid CSV file! Row " << i + 1 << " on column " << j + 1 << " does not match the intended type! " << "(expected " << dataTypeToStr(columnDataTypes[j]) << ')' << endl;
                    }

                    cout << endl;
                    isValid = false;
                }
            }
        }

        if (!isValid)
        {
            std::exit(-1);
        }
    }

    void removeDuplicates() {
        vector<vector<string>> uniqueRows;

        size_t rowsCount = data.size();

        for (size_t i = 0; i < rowsCount; i++)
        {
            const vector<string>& row = data[i];

            if (std::find(uniqueRows.begin(), uniqueRows.end(), row) == uniqueRows.end()) {
                uniqueRows.push_back(row);
            }
        }

        if (rowsCount != uniqueRows.size())
        {
            data = uniqueRows;
            isModified = true;
        }     
    }

private:
    // This method took my soul
    vector<string> parseCSVLine(const string& line) {
        vector<string> rowData;
        stringstream ss(line);
        string cell;

        while (std::getline(ss, cell, ',')) {
            bool isQuotedData = false;

            if (!cell.empty()) {
                // Check if the cell starts with " or ' and doesn't end with " or '
                if (cell.front() == '"' || cell.front() == '\'') {

                    // Combine subsequent cells until we find one that ends with " or '
                    if ((cell.back() == '"' || cell.front() == '\'') && cell.length() > 1) {
                        rowData.push_back(cell);
                        continue;
                    }

                    string combinedCell = cell;

                    while (std::getline(ss, cell, ',')) {
                        combinedCell += ',' + cell;
                        if (!cell.empty() && (cell.back() == '"' || cell.back() == '\'')) {
                            isQuotedData = true;
                            break;
                        }
                    }

                    if (isQuotedData) {
                        rowData.push_back(trim(combinedCell));
                    }

                    else {
                        // The combined cell doesn't end with " or ', treat it as normal data
                        string finalStr = combinedCell + ',' + cell;
                        rowData.push_back(trim(finalStr));
                    }
                }
                else {
                    rowData.push_back(trim(cell));
                }
            }
            else {
                rowData.push_back("");
            }
        }

        // That happens when the last cell of the row is empty, this if-statement takes care of it
        if (columnNames.size() - 1 == rowData.size())
        {
            rowData.push_back("");
        }

        return rowData;
    }

    inline string& trim(string& str)
    {
        str.erase(str.find_last_not_of(' ') + 1);
        str.erase(0, str.find_first_not_of(' '));

        return str;
    }

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

        size_t cycles = str.size();

        if (cycles == 0)
        {
            cout << "Invalid string!" << endl;
            return -1;
        }

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

        size_t columnsCount = data.size();

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

        size_t columnsCount = data.size();

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

        size_t columnsCount = data.size();

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
};