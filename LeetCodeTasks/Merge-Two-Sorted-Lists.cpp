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

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
	ListNode* dummy, * temp;
	dummy = new ListNode();
	temp = dummy;

	while (list1 && list2) {
		if (list1->val < list2->val) {
			temp->next = list1;
			list1 = list1->next;
		}
		else {
			temp->next = list2;
			list2 = list2->next;
		}
		temp = temp->next;
	}

	if (list1) temp->next = list1;
	if (list2) temp->next = list2;

	return dummy->next;
}

int main()
{
	/*ListNode AAA(4);
	ListNode AAa(3, &AAA);
	ListNode Aaa(2, &AAa);
	ListNode aaa(1, &Aaa);


	ListNode BBB(7);
	ListNode BBb(6, &BBB);
	ListNode Bbb(5, &BBb);
	ListNode bbb(4, &Bbb);

	ListNode* result = mergeTwoLists(&aaa, &bbb);

	while (result->next != nullptr)
	{
		cout << result->val;
		result = result->next;
	}

	delete result;*/
}