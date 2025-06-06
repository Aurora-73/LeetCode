// MyListNode.cpp
#include "MyListNode.h"

using namespace std;

ListNode *createList(int n) {
	if(n <= 0) return nullptr;

	ListNode *head = new ListNode(1);
	ListNode *current = head;

	for(int i = 2; i <= n; i++) {
		current->next = new ListNode(i);
		current = current->next;
	}
	return head;
}

ListNode *createList(const vector<int> &values) {
	if(values.empty()) return nullptr;

	ListNode *head = new ListNode(values[0]);
	ListNode *current = head;

	for(size_t i = 1; i < values.size(); i++) {
		current->next = new ListNode(values[i]);
		current = current->next;
	}

	return head;
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
