#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::vector;
using std::endl;

struct ListNode {
	int val;
	ListNode* next;

	ListNode() : val(0), next(nullptr) {

	}
	ListNode(int x) : val(x), next(nullptr) {

	}
	ListNode(int x, ListNode* next) : val(x), next(next) {

	}
};

ListNode* reverseList(ListNode* head)
{
	ListNode* prev = nullptr;

	while (head != NULL) {
		ListNode* next = head->next;
		head->next = prev;
		prev = head;
		head = next;
	}
	return prev;
}

int main()
{
	ListNode AAA(4);
	ListNode AAa(3, &AAA);
	ListNode Aaa(2, &AAa);
	ListNode aaa(1, &Aaa);

	ListNode* result = reverseList(&aaa);

	while (result != nullptr)
	{
		cout << result->val;
		result = result->next;
	}

	delete result;
}