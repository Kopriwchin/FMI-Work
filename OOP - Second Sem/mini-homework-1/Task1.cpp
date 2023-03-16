/*
	A color has 3 components: red, green, and blue.
	
	Make a structure 'Color' that will hold the data of a primitive color (3 bits).
	Example: RED -> 100 / GREEN -> 010 / BLUE -> 001.

	Make a function that prints the name of a given Color.
	
	Make a function that takes a Color and returns the opposite Color.
	
	Make a function that fuses a Color with a second Color 
	and a function that removes a Color from a Color.
*/

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

void decToBinary(int n)
{
	int binaryNum[32];

	int i = 0;
	while (n > 0) {

		binaryNum[i] = n % 2;
		n /= 2;
		i++;
	}

	for (int j = i - 1; j >= 0; j--)
		cout << binaryNum[j];

	cout << endl;
}


enum EnumColor {
	Unknown = -1,
	Blue = int(0b00000001),
	Green = int(0b00000010),
	Cyan = int(0b00000011),
	Red = int(0b00000100),
	Pink = int(0b00000101),
	Yellow = int(0b0000110),
	White = int(0b0000111),
};

struct Color {
	char color;
};

//void PrintColor(Color color) {
//	cout << *((char*)&color);
//}

Color GetOppositeColor (Color myColor)
{
	Color oppositeColor = { myColor.color ^ 0b00000111 };
	return oppositeColor;
}

Color FuseTwoColors(Color firstColor, Color secondColor)
{
	Color newColor = { firstColor.color | secondColor.color };
	return newColor;
}

void PrintNameOfColor(Color inputColor)
{
	int intColor = (int)inputColor.color;

	switch (intColor)
	{
		case Unknown:
			cout << "Unknown color!" << endl;
			break;
		case Blue:
			cout << "The color is Blue!" << endl;
			break;
		case Green:
			cout << "The color is Green!" << endl;
			break;
		case Cyan:
			cout << "The color is Cyan!" << endl;
			break;
		case Red:
			cout << "The color is Red!" << endl;
			break;
		case Pink:
			cout << "The color is Pink!" << endl;
			break;
		case Yellow:
			cout << "The color is Yellow!" << endl;
			break;
		case White:
			cout << "The color is White!" << endl;
			break;
	}
}

int main() {
	// Test examples
	
	Color myColor = { 0b00000001 }; // Blue

	Color anotherColor = { 0b00000100 }; // Red

	// Should print "Blue"
	PrintNameOfColor(myColor);

	// Returned color should be "Cyan"
	Color oppositeColor = GetOppositeColor(anotherColor);
	PrintNameOfColor(oppositeColor);

	// Should return a Color with value color -> "101" (Pink)
	Color fusedColor = FuseTwoColors(myColor, anotherColor);
	PrintNameOfColor(fusedColor);

	return 0;
}