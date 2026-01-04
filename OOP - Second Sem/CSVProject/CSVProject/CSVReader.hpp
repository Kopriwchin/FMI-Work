#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "CSVParser.hpp"
#include "CSVSort.hpp"
#include "CSVDataType.hpp"

using std::ifstream;
using std::ofstream;

using std::string;
using std::stringstream;
using std::vector;

using std::cout;
using std::endl;

class CSVReader : public CSVParser
{
private:
    string filename;
    vector<string> columnNames;
    vector<DataType> columnDataTypes;
    vector<vector<string>> data;

public:
    CSVReader(const string& filename) : filename(filename) {};

    bool open(bool hasHeaderRow = true) {
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

            if (row.size() != 0)
            {
                data.push_back(row);
            }

            row.clear();
        }

        file.close();
        return true;
    }

    /*void save()
    {
        ofstream file(filename);

        if (!file || !file.is_open())
        {
            cout << INVALID_FILE_MSG << endl;
            return;
        }

        int columnsCount = data[0].size();
        int rowsCount = data.size();

        for (size_t i = 0; i < rowSize; ++i)
        {
            for (size_t j = 0; j < columnsCount; j++)
            {

            }
        }
    }*/

    const vector<vector<string>> getData() const {
        return data;
    }

    const string getFilename() const
    {
        return filename;
    }

    void printHeaderRow() const
    {
        if (columnNames.empty())
            return;

        int columnsCount = columnNames.size();

        for (size_t i = 0; i < columnsCount; ++i)
        {
            cout << std::left << std::setw(20) << columnNames[i].c_str();
        }

        cout << endl;
    }
    
    void printRow(int index) const
    {
        int rowsCount = data.size();
        int columnsCount = data[0].size();

        if (index >= rowsCount || index < 0)
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

    void printColumn(int index) const
    {
        int rowsCount = data.size();

        if (index >= rowsCount || index < 0)
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
        int columsCount = columnNames.size();

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

    void printData(int rowsToPrint = 10) const
    {
        printHeaderRow();

        int rowsCount = data.size();

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

        int columnsCount = data[0].size();

        for (size_t i = 0; i < rowsToPrint; ++i)
        {
            for (size_t j = 0; j < columnsCount; ++j)
                cout << std::left << std::setw(20) << data[i][j];
            //printRow(i);

            cout << endl;
        }

        cout << endl;
    }

    int getColumnIndex(const string& name) const
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

    DataType getDataTypeOfColumn(int columnIndex)
    {
        return columnDataTypes[columnIndex];
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
        int rowsCount = data.size();

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
    }
   
    bool validateColumnTypes() {
        if (data.empty()) {
            cout << "No data loaded! Please load the CSV file first." << endl;
            return false;
        }

        int columnsCount = data[0].size();
        vector<DataType> columnTypes(columnsCount);

        for (size_t i = 0; i < columnsCount; ++i)
        {
            columnTypes[i] = DataType::Unknown;
        }

        // Determine column data types
        // should the vector be a const??????????????????

        int rowsCount = data.size();

        for (size_t i = 0; i < rowsCount; ++i)
        {
            vector<string> row = data[i];

            for (size_t j = 0; j < columnsCount; ++j) {
                string trimmedCell = trim(row[j]);

                if (columnTypes[j] == DataType::Unknown) {
                    // First non-empty value encountered, determine its type
                    columnTypes[j] = inferDataType(trimmedCell);
                }
                else if (inferDataType(trimmedCell) != columnTypes[j]) {
                    // Type mismatch detected
                    // Calculate the position of the bad data
                    if (!columnNames.empty())
                    {
                        cout << "Invalid CSV file! Row " << i + 2 << " on column " << j + 1 << " does not match the intended type! " << "(expected " << dataTypeToStr(columnTypes[j]) << ')' << endl;
                    }
                    else
                    {
                        cout << "Invalid CSV file! Row " << i + 1 << " on column " << j + 1 << " does not match the intended type! " << "(expected " << dataTypeToStr(columnTypes[j]) << ')' << endl;
                    }

                    cout << endl;

                    return false;
                }
            }
        }

        return true;
    }

    void removeDuplicates() {
        //https://stackoverflow.com/questions/1041620/whats-the-most-efficient-way-to-erase-duplicates-and-sort-a-vector
        //sort(data.begin(), data.end());
        //data.erase(std::unique(data.begin(), data.end()), data.end());

        vector<vector<string>> uniqueRows;

        int rowsCount = data.size();

        for (size_t i = 0; i < rowsCount; i++)
        {
            const vector<string>& row = data[i];

            if (std::find(uniqueRows.begin(), uniqueRows.end(), row) == uniqueRows.end()) {
                uniqueRows.push_back(row);
            }
        }

        data = uniqueRows;
    }

    friend class CSVSort;
    friend class CSVDataType;
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
};