// Created: 2025-04-28
#include "MyUtils.h"
#include "ListNode.h"
/*61. 旋转链表
给你一个链表的头节点 head ，旋转链表，将链表每个节点向右移动 k 个位置。*/

class Solution1 {
public:
	ListNode *rotateRight(ListNode *head, int k) {
		int length = 0;
		for(ListNode *now = head; now; now = now->next, length++)
			;
		if(length < 2) {
			return head;
		} // 先判断长度后取余，防止除 0 异常
		k %= length;
		if(k == 0) {
			return head;
		} // 先取余后判断，防止移动步数等于长度
		ListNode headNode(-1, head);
		reverseAfterhead(&headNode);
		ListNode *tail = headNode.next, *now = &headNode, *head2;
		for(int i = 0; i < k; i++) {
			now = now->next;
		}
		head2 = now->next;
		now->next = nullptr;
		reverseAfterhead(&headNode);
		tail->next = head2;
		reverseAfterhead(tail);
		return headNode.next;
	}
	void reverseAfterhead(ListNode *head) {
		ListNode *now = head->next;
		head->next = nullptr;
		while(now) {
			ListNode *temp = now->next;
			now->next = head->next;
			head->next = now;
			now = temp;
		}
	}
};

class Solution2 {
public:
	ListNode *rotateRight(ListNode *head, int k) {
		if(!head || k < 1)
			return head;
		int length = 1;
		ListNode *tail = head;
		while(tail->next) {
			tail = tail->next;
			length++;
		}
		k = length - k % length;
		if(length < 2 || k == length) {
			return head;
		}
		tail->next = head;
		while(k--) {
			tail = tail->next;
		}
		head = tail->next;
		tail->next = nullptr;
		return head;
	}
};

int main() {
	ListNode *head = createList(9);
	cout << head << endl;
	Solution1 sol1;
	head = sol1.rotateRight(head, 3);
	cout << head << endl;
	Solution2 sol2;
	head = sol2.rotateRight(head, 3);
	cout << head << endl;
	deleteList(head);
}