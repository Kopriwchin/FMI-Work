#include <iostream>

using namespace std;

int main()
{
	double myX, myY, batMobileX, batMobileY;

	cin >> myX >> myY >> batMobileX >> batMobileY;

	if ((myX - batMobileX >= -0.1 && myX - batMobileX <= 0.1) && 
		(myY - batMobileY >= -0.1 && myY - batMobileY <= 0.1))
	{
		cout << "You're there already!";
	}
	else if (myX == batMobileX)
	{
		if (myY < batMobileY)
		{
			cout << "N";
		}
		else
		{
			cout << "S";
		}
	}
	else if (myY == batMobileY)
	{
		if (myX < batMobileX)
		{
			cout << "E";
		}
		else
		{
			cout << "W";
		}
	}
	else if (myX < batMobileX)
	{
		if (myY < batMobileY)
		{
			cout << "NE";
		}
		else
		{
			cout << "SE";
		}
	}
	else if (myX > batMobileX) {
		if (myY < batMobileY)
		{
			cout << "NW";
		}
		else {
			cout << "SW";
		}
	}
}