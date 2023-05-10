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

ListNode* middleOfLinkedList(ListNode* head)
{
	ListNode* slowNode = head;
	ListNode* fastNode = head;

	while (fastNode && fastNode->next)
	{
		slowNode = slowNode->next;
		fastNode = fastNode->next->next;
	}

	return slowNode;
}

int main()
{
	ListNode AAAAA(6);
	ListNode AAAA(5, &AAAAA);
	ListNode AAA(4, &AAAA);
	ListNode AAa(3, &AAA);
	ListNode Aaa(2, &AAa);
	ListNode aaa(1, &Aaa);

	ListNode* result = middleOfLinkedList(&aaa);

	while (result != nullptr)
	{
		cout << result->val;
		result = result->next;
	}

	delete result;
}