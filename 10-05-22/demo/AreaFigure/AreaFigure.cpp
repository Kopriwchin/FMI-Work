#include <iostream>

using namespace std;

int main()
{
	char figureChar;

	cin >> figureChar;

	if (figureChar == 's')
	{
		double size;
		cin >> size;
		
		cout << size * size;
	} 
	else if (figureChar == 'r') 
	{
		double length;
		cin >> length;
		double width;
		cin >> width;

		cout << length * width;
	}
	else if (figureChar == 'c')
	{
		double radius;
		cin >> radius;

		cout << 3.14 * radius * radius;
	}
}