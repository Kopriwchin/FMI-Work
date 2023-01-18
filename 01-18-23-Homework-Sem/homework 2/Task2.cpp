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

char ReturnSymbol(string morse)
{
    string englishLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789,.?/";

    string lettersMorse[42] = { ".-", "-...", "-.-.", "-..", ".", "..-.","--.", "....",
        "..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.",
        "--.-", ".-.", "...", "-", "..-", "...-", ".--", "-..-",
        "-.--", "--..", "-----", ".----","..---","...--", "....-",
        ".....","-....","--...","---..","----.",  "--..--", ".-.-.-", "..--..", "-..-.", ".--.-."};
    

    for (size_t i = 0; i < 42; i++)
    {
        if (morse == lettersMorse[i])
        {
            return englishLetters[i];
        }
    }
}

string Decode(string code)
{
    // Another way (could've used the same method in Encode)
    int spacesCount = 0;
    for (size_t i = 0; i < code.length(); i++)
    {
        if (code[i] = ' ')
        {
            spacesCount++;
        }
    }

    char* finalMessage = new char[100];

    for (size_t i = 0; i < spacesCount; i++)
    {
        string initWord = "";

        for (size_t j = 0; j < 6; j++)
        {
            initWord += ReturnSymbol(code[i]);
            if (code[i] == ' ')
            {
                
            }
            
        }
    }

    return code;
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
    else
    {
        string* morseCode = Decode(message);

        for (size_t i = 0; i < message.length(); i++)
        {
            cout << morseCode[i];
        }

        delete[] morseCode;
    }
    

    return 0;
}