// Created: 2025-04-28
#include "MyUtils.h"
#include "MyListNode.h"
/*  25. K 个一组翻转链表
给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。
k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。*/

class Solution1 {
public:
	ListNode *reverseKGroup(ListNode *head, int k) {
		ListNode headNode(-1, head);
		ListNode *left = &headNode, *right = &headNode, *next;
		while(right) {
			for(int i = 0; i < k && right; i++) {
				right = right->next;
			}
			if(!right)
				break;
			next = right->next;
			right->next = nullptr;
			right = left->next;
			reverseListAfterHead(left);
			left = right;
			left->next = next;
		}
		return headNode.next;
	}
	ListNode *reverseListAfterHead(ListNode *head) {
		ListNode *now = head->next;
		head->next = nullptr;
		while(now) {
			ListNode *temp = now->next;
			now->next = head->next;
			head->next = now;
			now = temp;
		}
		return head;
	}
};

class Solution {
public:
	ListNode *reverseKGroup(ListNode *head, int k) {
		if(k == 1 || !head)
			return head;
		ListNode *left = head, *right = head, *next, *prev = nullptr;
		while(right) {
			for(int i = 1; i < k && right; i++) {
				right = right->next;
			}
			if(!right)
				break;
			next = right->next;
			if(prev) {
				prev->next = right;
			} else {
				head = right;
			}
			prev = left;
			ListNode *pre = right->next, *temp;
			while(left != next) {
				temp = left->next;
				left->next = pre;
				pre = left;
				left = temp;
			}
			left = right = next;
		}
		return head;
	}
};

int main() {
	ListNode *head = createList(20);
	cout << head << endl;
	Solution sol1;
	head = sol1.reverseKGroup(head, 4);
	cout << head << endl;
	deleteList(head);
}