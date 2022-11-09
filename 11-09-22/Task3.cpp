#include <iostream>
#include <math.h>
using namespace std;

double returnDistance(int x1, int y1, int x2, int y2)
{
	return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

double returnPerimeter(int x1, int y1, int x2, int y2, int x3, int y3) {
	double a, b, c;


	a = returnDistance(x1, y1, x2, y2);
	b = returnDistance(x1, y1, x3, y3);
	c = returnDistance(x3, y3, x2, y2);

	return a + b + c;
}

int main() {
	int x1, y1, x2, y2, x3, y3;

	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

	double result = returnPerimeter(x1, y1, x2, y2, x3, y3);

	cout << result;
}