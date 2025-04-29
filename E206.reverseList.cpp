// Created: 2025-04-25
#include "MyUtils.h"
#include "MyListNode.h"
/*  */

class Solution1 {
public:
	ListNode *reverseList(ListNode *head) {
		ListNode *headNode = new ListNode();
		while(head) {
			ListNode *temp = head;
			head = head->next;
			temp->next = headNode->next;
			headNode->next = temp;
		}
		head = headNode->next;
		delete headNode;
		return head;
	}
}; // 有头结点

class Solution2 {
public:
	ListNode *reverseList(ListNode *head) {
		if(!head)
			return head;
		ListNode *pre = nullptr, *now = head;
		while(now) {
			ListNode *next = now->next;
			now->next = pre;
			pre = now;
			now = next;
		}
		return pre;
	}
}; // 无头结点

int main() {
	ListNode *head = createList(5);
	cout << head << endl;
	Solution1 sol1;
	head = sol1.reverseList(head);
	cout << head << endl;
	Solution2 sol2;
	head = sol2.reverseList(head);
	cout << head << endl;
	deleteList(head);
}