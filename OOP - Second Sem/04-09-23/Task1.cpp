#include <iostream>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;

using std::ifstream;
using std::ofstream;

struct Point {
    float x;
    float y;
};

unsigned getPoints(ifstream& pointsFile) {
    int curr;
    pointsFile.seekg(0, std::ios::end);
    curr = pointsFile.tellg();
    pointsFile.seekg(0, std::ios::beg);

    return curr / sizeof(Point);
}

void printPoints() {
    const char* INVALID_FILE_MSG = "Error! Could not open file for reading!";
    std::ifstream pointsFile("input-points.dat", std::ios::binary);

    if (!pointsFile || !pointsFile.is_open())
    {
        cout << INVALID_FILE_MSG << endl;
        return;
    }

    unsigned getPointsCount = getPoints(pointsFile);
    Point initPoint;

    for (size_t i = 0; i < getPointsCount; i++)
    {
        pointsFile.read(reinterpret_cast<char*>(&initPoint), sizeof(Point));
        cout << "Points are:" << endl;
        cout << "X: " << initPoint.x << endl;
        cout << "Y: " << initPoint.y << endl;
    }

    // I know that the stream closes by itself at the end of the scope, but good practice :)
    pointsFile.close();
}

void writePoint(Point& point) {
    const char* INVALID_FILE_MSG = "Error! Could not open file for writing!";

    std::ofstream pointsFile("input-points.dat", std::ios::binary);

    if (!pointsFile || !pointsFile.is_open())
    {
        cout << INVALID_FILE_MSG << endl;
        return;
    }

    pointsFile.write(reinterpret_cast<const char*>(&point), sizeof(Point));

    pointsFile.close();
}


int main()
{
   /* const char* FILE_NAME = "input-points.dat";

    double radius;
    cin >> radius;*/


}