#include <iostream>
#include <math.h>
using namespace std;

double returnDistance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

int main() {
	int x1, y1, x2, y2;

	cin >> x1 >> y1 >> x2 >> y2;

	double result = returnDistance(x1, y1, x2, y2);

	cout << result;
}