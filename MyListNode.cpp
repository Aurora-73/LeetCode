// MyListNode.cpp
#include "MyListNode.h"

using namespace std;

ListNode *createList(int n) {
	if(n <= 0) return nullptr;

	ListNode *head = new ListNode(1);
	ListNode *tail = head;

	for(int i = 2; i <= n; i++) {
		tail->next = new ListNode(i);
		tail = tail->next;
	}
	return head;
}

ListNode *createList(const std::initializer_list<int> &values) {
	ListNode dummy, *tail = &dummy;
	for(int v : values) {
		tail->next = new ListNode(v);
		tail = tail->next;
	}
	return dummy.next;
}

ostream &operator<<(ostream &os, ListNode *head) {
	os << "{ ";
	while(head) {
		os << head->val;
		head = head->next;
		if(head) {
			os << " -> ";
		}
	}
	return os << " }";
}

void deleteList(ListNode *head) {
	while(head) {
		ListNode *temp = head;
		head = head->next;
		delete temp;
	}
}
