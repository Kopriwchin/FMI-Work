#pragma once

using std::string;
using std::regex;

class CSVDataType
{
public:
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
        return std::regex_match(value, regex(R"(^\d{4}-\d{2}-\d{2}$)"));
    }

    bool isFacultyNumber(const string& value) {
        return std::regex_match(value, regex(R"(\dMI(0[1-9]|09)\d{5}\b)"));
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
};