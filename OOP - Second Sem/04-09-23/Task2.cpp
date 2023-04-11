#pragma warning (disable:4996)
#include <iostream>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;

enum class Gender {
    Unknown = 0,
    Male,
    Female
};

class Person {
public:
    Person() {
        this->firstName = new char[8];
        this->lastName = new char[8];

        strcpy(firstName, "Unknown");
        strcpy(lastName, "Unknown");
        gender = Gender::Unknown;
        yearOfBirth = 0;
    };

    Person(const char* firstName, const char* lastName, Gender gender, short yearOfBirth) {
        this->firstName = new char[strlen(firstName) + 1];
        this->lastName = new char[strlen(lastName) + 1];

        strcpy(this->firstName, firstName);
        strcpy(this->lastName, lastName);
        this->gender = gender;
        this->yearOfBirth = yearOfBirth;
    }

    Person& operator=(const Person& otherPerson) {
        if (this != &otherPerson) {
            free();
            copy(otherPerson);
        }

        return *this;
    }

    Person(const Person& otherPerson) {
        copy(otherPerson);
    }

    ~Person() {
        delete[] firstName;
        delete[] lastName;

        firstName = nullptr;
        lastName = nullptr;

        gender = Gender::Unknown;
        yearOfBirth = 0;
    }

    char* getFirstName() const {
        return this->firstName;
    }
    char* getLastName() const {
        return this->lastName;
    }
    const char* getGender() const {
        if (this->gender == Gender::Male)
            return "Male";
        else if (this->gender == Gender::Female)
            return "Female";
        else
            return "Unknown";
    }
    short getYearOfBirth() const {
        return this->yearOfBirth;
    }

private:
    char* firstName;
    char* lastName;
    Gender gender;
    short yearOfBirth;

    void copy(const Person& person) {
        this->firstName = new char[strlen(person.firstName) + 1];
        this->lastName = new char[strlen(person.lastName) + 1];
        strcpy(this->firstName, person.firstName);
        strcpy(this->lastName, person.lastName);
        
        this->gender = person.gender;
        this->yearOfBirth = person.yearOfBirth;
    }

    void free() {
        delete[] firstName;
        delete[] lastName;
        gender = Gender::Unknown;
        yearOfBirth = 0;
    }
};

class Car {
public:
    Car() {
        strcpy(model, "Unknown");
        owner = nullptr;
        yearOfRegistration = 0;
    }

    Car(const char model[128], Person& owner, short yearOfRegistration) {
        strcpy(this->model, model);
        this->owner = &owner;
        this->yearOfRegistration = yearOfRegistration;
    }

    void readFromFile(int carsCount) {
        const char* INVALID_READ_FILE_MSG = "Error! Could not open file for reading!";

        ifstream carsFile("cars.txt");

        if (!carsFile || !carsFile.is_open()) {
            cout << INVALID_READ_FILE_MSG << endl;
            return;
        }

        // Easier if carsCount is being passed through parameter
        //int carsCount = getCarsCount(carsFile);

        if (carsCount == 0) {
            cout << "No cars to show.." << endl;
            return;
        }

        const unsigned BUFFER_SIZE = 1024;

        for (size_t i = 0; i < carsCount; i++) {
            char buffer[BUFFER_SIZE];
            carsFile.getline(buffer, BUFFER_SIZE);
            cout << buffer << endl;
        }

        carsFile.close();
    }

    void writeToFile(Car cars[], int carsCount) {
        const char* INVALID_WRITE_FILE_MSG = "Error! Could not open file for writing!";

        ofstream carsFile("cars.txt", std::ios::app);

        if (!carsFile || !carsFile.is_open()) {
            cout << INVALID_WRITE_FILE_MSG << endl;
            return;
        }

        for (size_t i = 0; i < carsCount; i++) {
            carsFile << "Car model: " << cars[i].model << " | Car owner: " << cars[i].owner->getFirstName() << " " << cars[i].owner->getLastName() << " | Car year of registration: " << cars[i].yearOfRegistration << endl;
        }

        carsFile.close();
    }

    /*
        No time left.. The idea is to sort the cars alphabetically, then strcmp(two of them),
        if it returns 0, then they are equal so we increment the counter by one,
        if it returns != 0, then we have another car so we set the counter to zero and check if (count > topModelCount),
        then at the end we see what is the car that is the most often used
    */

    /*
        char* getMostUsedCarModel(int carsCount) {
            const char* INVALID_READ_FILE_MSG = "Error! Could not open file for reading!";

            ifstream carsFile("cars.txt");

            if (!carsFile || !carsFile.is_open()) {
                cout << INVALID_READ_FILE_MSG << endl;
                return;
            }

            if (carsCount == 0) {
                cout << "No cars to show.." << endl;
                return;
            }

            char* topModel;
            int topModelCount = 0;
            int count;

            for (size_t i = 0; i < carsCount; i++) {

            }
        }
    */

private:
    char model[128];
    Person* owner;
    short yearOfRegistration;

    /*
        int getCarsCount(ifstream& carsFile) const {
             int curr = 0;
             carsFile.seekg(0, std::ios::end);
             curr = carsFile.tellg();
             carsFile.seekg(0, std::ios::beg);

             return curr / sizeof(Car);
         }
     */
};


int main() {
    Person newPerson("Gosho", "Petrov", Gender::Male, 2000);
    cout << newPerson.getFirstName() << endl;
    cout << newPerson.getLastName() << endl;
    cout << newPerson.getGender() << endl;
    cout << newPerson.getYearOfBirth() << endl;

    Person anotherPerson;
    anotherPerson = newPerson;

    cout << anotherPerson.getFirstName() << endl;
    cout << anotherPerson.getLastName() << endl;
    cout << anotherPerson.getGender() << endl;
    cout << anotherPerson.getYearOfBirth() << endl;

    /*Car cars[2];
    cars[0] = Car("Mercedes", newPerson, 2000);
    cars[1] = Car("BMW", anotherPerson, 2003);

    cars[0].writeToFile(cars, 2);
    cars[0].readFromFile(2);*/
}