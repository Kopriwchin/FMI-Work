#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::string;

bool IsLetter(char letter)
{
    if (letter >= 'A' && letter <= 'Z')
    {
        return true;
    }

    return false;
}

bool IsDigit(char number)
{
    if (number >= '0' && number <= '9')
    {
        return true;
    }

    return false;
}

string OtherSymbols(char symbol)
{
    switch (symbol)
    {
        case '.':
            return ".-.-.-";
            break;

        case ',':
            return "--..--";
            break;

        case '?':
            return "..--..";
            break;

        case '/':
            return "-..-.";
            break;

        case '@':
            return ".--.-.";
            break;

        default:
            return " ";
            break;
    }


}

string* Encode(string message)
{
    string* morseMessage = new string[message.length()];

    // A - Z
    string morseCodeAlphabet[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....",
            "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.",
            "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
            "-.--", "--.."};

    // 0 - 9
    string numbersMorse[] = { "-----", ".----","..---","...--", "....-",".....","-....","--...","---..","----." };

    for (size_t i = 0; i < message.length(); i++)
    {
        char currentSymbol = message[i];

        if (IsLetter(currentSymbol))
        {
            morseMessage[i] = morseCodeAlphabet[currentSymbol - 'A'];
        }
        else if (IsDigit(currentSymbol))
        {
            morseMessage[i] = morseCodeAlphabet[currentSymbol - '0'];
        }
        else
        {
            morseMessage[i] = OtherSymbols(currentSymbol);
        }
    }

    return morseMessage;
}

string Decode(string code)
{
    string morseCodeAlphabet[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....",
         "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.",
         "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
         "-.--", "--.." };
    
    string numbersMorse[] = { "-----", ".----","..---","...--", "....-",".....","-....","--...","---..","----." };

    for (size_t i = 0; i < code.length(); i++)
    {

    }
}

int main()
{
    string option;
    cin >> option;

    string message;

    std::cin.ignore();
    std::getline(cin, message);

    if (option == "encode")
    {
        string* morseCode = Encode(message);

        for (size_t i = 0; i < message.length(); i++)
        {
            cout << morseCode[i];
        }

        delete[] morseCode;
    }
    /*else
    {
        string* morseCode = Decode(message);

        for (size_t i = 0; i < message.length(); i++)
        {
            cout << morseCode[i];
        }

        delete[] morseCode;
    }
    */

    return 0;
}