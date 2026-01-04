#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>
#include <iomanip>

#include "Constants.hpp"
#include "CSVReader.hpp"
#include "CSVWriter.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

int main()
{
    CSVReader reader("students.csv");
    
    reader.open();

    reader.printData(20);

    

    /*
    reader.removeDuplicates();

    reader.printData();*/

    //reader.validateColumnTypes();

    //reader.printData();
    //reader.removeDuplicates();
    //reader.sortColumn(5);
    //reader.filter(4, ">=", "5000");
}