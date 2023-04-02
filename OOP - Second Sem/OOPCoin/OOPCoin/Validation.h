#pragma once

using std::cin;
using std::cout;
using std::endl;

void validateAmount(double& amount) {
	while (true) {
		if (amount < 0) {
			cout << "\t\tInvalid input! Amount must be a positive number!" << endl;
			cout << "Enter amount: ";
			cin >> amount;
			if (!cin)
			{
				cout << "Invalid input!" << endl;
				exit(-1);
			}
			continue;
		}
		break;
	}
}

void validateName(char* name) {
	while (true) {
		if (strlen(name) < 4 || strlen(name) > 127) {
			cout << "\t\tInvalid input! Name length must be between 4 and 127 characters!" << endl;
			cout << "Enter username: ";
			cin >> name;
			continue;
		}
		break;
	}
}