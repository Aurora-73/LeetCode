// Created: 2025-04-25
#include "MyUtils.h"
#include "MyListNode.h"

/* 给你单链表的头指针 head 和两个整数 left 和 right ，其中 left <= right 。
请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表 。 */

class Solution1 {
public:
	ListNode *reverseBetween(ListNode *head, int left, int right) {
		if(left == right) {
			return head;
		}

		ListNode *dummy = new ListNode(0, head);
		ListNode *pre = dummy;

		// 找到 left-1 的节点
		for(int i = 0; i < left - 1; ++i) {
			pre = pre->next;
		}

		ListNode *start = pre->next;
		ListNode *end = start;
		for(int i = left; i < right; ++i) {
			end = end->next;
		}

		ListNode *next = end->next;
		// 断开 [start, end]
		end->next = nullptr;
		pre->next = reverse(start);
		start->next = next;

		head = dummy->next;
		delete dummy;
		return head;
	}

private:
	ListNode *reverse(ListNode *head) {
		ListNode *prev = nullptr;
		while(head) {
			ListNode *next = head->next;
			head->next = prev;
			prev = head;
			head = next;
		}
		return prev;
	}
};

class Solution2 {
public:
	ListNode *reverseBetween(ListNode *head, int left, int right) {
		if(left == right) {
			return head;
		}

		ListNode dummy(0, head);
		ListNode *pre = &dummy;

		for(int i = 1; i < left; ++i) {
			pre = pre->next;
		}

		ListNode *curr = pre->next;
		for(int i = 0; i < right - left; ++i) {
			ListNode *temp = curr->next;
			curr->next = temp->next;
			temp->next = pre->next;
			pre->next = temp;
		}

		return dummy.next;
	}
};

int main() {
	ListNode *head = createList(6);
	cout << head << endl;
	Solution1 sol1;
	sol1.reverseBetween(head, 2, 4);
	cout << head << endl;
	Solution2 sol2;
	sol2.reverseBetween(head, 2, 4);
	cout << head << endl;
}