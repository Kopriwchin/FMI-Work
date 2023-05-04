#include <iostream>
#include <string>

using std::cout;
using std::string;
using std::endl;

bool isIsomorphic(string s, string t) {
	char firstWordAlphabet[256] {0};
	char secondWordAlphabet[256] {0};
	int length = t.length();

	if (s.length() != length)
		return false;

	for (int i = 0; i <= length; i++)
	{
		if (firstWordAlphabet[s[i]] != secondWordAlphabet[t[i]])
		{
			return false;
		}
		firstWordAlphabet[s[i]] = i + 1;
		secondWordAlphabet[t[i]] = i + 1;
	}

	return true;
}

int main()
{
	cout << isIsomorphic("daaf", "bddb") << endl;
	cout << isIsomorphic("aacd", "hhdc") << endl;
}