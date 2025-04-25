// Created: 2025-04-25
#include "MyUtils.h"

/*  */

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

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
		return now;
	}
}; // 无头结点

int main() {
	Solution1 sol;
	Solution2 sol;
}