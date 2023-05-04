#include <iostream>
#include <string>

using std::cout;
using std::string;
using std::endl;

bool isSubsequence(string s, string t) {
	int subLength = s.length();
	int textLength = t.length();
	int index = 0;

	if (subLength > textLength)
	{
		return false;
	}

	if (subLength == 0)
	{
		return true;
	}

	for (int i = 0; i < textLength; i++)
	{
		if (s[index] == t[i])
		{
			index++;

			if (index == s.length())
			{
				return true;
			}
		}

	}
	
	return false;
}

int main()
{
	cout << isSubsequence("abc", "ahbgdc") << endl; // true
	cout << isSubsequence("axc", "ahbgdc") << endl; // false
	cout << isSubsequence("a", "a") << endl; // true
	cout << isSubsequence("", "") << endl; // true
	cout << isSubsequence("abc", "aacb") << endl; // false
}