#pragma once

#include <iostream>
#include <vector>
#include <fstream>

using std::string;
using std::vector;

class CSVParser {
protected:
    string filename;
    vector<vector<string>> data;
public:
    CSVParser(const string& filename) : filename(filename) {}

    virtual bool loadCSV() = 0;

    const vector<vector<string>>& getData() const {
        return data;
    }
};