#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

struct Person
{
	string name;
	int age;
	char drinks;
};

/* Cool task to create a program that maintains bar clients and their favourite drinks
	with bitwise operations by saving everything in 8-bit variable. (in this case - char) */

int main()
{
	// Order of beverages
	/*
	whiskey - 0
	vodka - 1
	candy - 2
	water - 3
	wine - 4
	*/

	char whiskey = 0b00000001;
	char vodka = 0b00000010;
	char candy = 0b00000100;
	char water = 0b00001000;
	char wine = 0b00010000;

	char name[] = "Petko";
	int age = 15;
	char preferenceDrinks = 0b00000000;

	// Adds whiskey and vodka to preferable drinks
	preferenceDrinks ^= whiskey;
	preferenceDrinks ^= vodka;

	Person person { name, age, preferenceDrinks };
	
	//cout << person.name << endl;
	//cout << person.age << endl;

	
	if (person.drinks & whiskey && person.drinks & vodka)
	{
		cout << person.name << " LIKES WHISKEY AND VODKA!" << endl;;
	}

	// Remove whiskey from person's preferable drinks
	person.drinks ^= whiskey;

	if (!(person.drinks & whiskey))
	{
		cout << person.name << " DOES NOT LIKE WHISKEY!" << endl;
	}

	return 0;
}