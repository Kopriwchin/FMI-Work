#include <iostream>
#include <cassert>

using std::cin;
using std::cout;
using std::endl;

template <typename T>
struct Element {
	T data;
	Element<T>* next;

	Element(const T& value) {
		data = value;
		next = nullptr;
	}
};

template <typename T>
struct Stack {
	size_t count;
	Element<T>* head;

	Stack() {
		count = 0;
		head = nullptr;
	}

	bool empty() const {
		return count == 0;
	}

	void push(const T& value) {
		Element<T>* newEl = new Element<T>(value);
		newEl->next = head;
		head = newEl;
		++count;
	}

	void pop() {
		assert(size() > 0);
		Element<T>* temp = head;
		head = head->next;
		--count;
		delete temp;
	}

	void clear() {
		assert(size() > 0);

		while (head != nullptr) {
			pop();
		}
		count = 0;
		head = nullptr;
	}

	T& peek() const {
		assert(size() > 0);

		return head->data;
	}

	size_t size() const {
		return count;
	}

};

int main()
{
	Stack<int> stack;
	stack.push(1);
	stack.push(2);
	stack.push(3);
	stack.push(4);

	stack.clear();
	cout << stack.size() << endl;

	stack.push(1);
	stack.push(2);
	stack.push(3);
	stack.push(4);
	cout << stack.size() << endl;

}