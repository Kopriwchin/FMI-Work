#include <iostream>
using namespace std;

int main()
{
    char sym;

    cin >> sym;

    if (sym == 'a' || sym == 'A' ||
        sym == 'e' || sym == 'E' ||
        sym == 'i' || sym == 'I' ||
        sym == 'o' || sym == 'O' ||
        sym == 'u' || sym == 'U') 
    {
        cout << 1;
    }
    else
    {
        cout << 0;
    }

    return 0;
}

