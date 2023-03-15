#include <iostream>
using namespace std;

struct UniProgram {
public:
	char programName[30];
	int year;
};

struct Student {
public:
	char name[50];
	short age;
	UniProgram* program;
};

void PrintStudentData(Student* student)
{
	cout << "Student name: " << student->name << endl;
	cout << "Student age: " << student->age << endl;
	cout << "Student program name: " << student->program->programName << endl;
	cout << "Student university year: " << student->program->year << endl;
}

int main()
{
	Student student1 = {
		"Pesho",
		21,
		new UniProgram {"Informatics", 5}
	};

	Student* student2 = &student1;

	PrintStudentData(&student1);
	cout << '\n';

	strcpy_s(student1.name, "Ivan");
	PrintStudentData(student2);
	
	return 0;
}