// Created: 2025-04-25
#include "MyListNode.h"
#include "MyUtils.hpp"

/* 给你单链表的头指针 head 和两个整数left 和 right，其中left <= right。
请你反转从位置 left 到位置 right 的链表节点，返回 反转后的链表。
示例 1：
	输入：head = {1,2,3,4,5}, left = 2, right = 4
	输出：{1,4,3,2,5}
示例 2：
	输入：head = {5}, left = 1, right = 1
	输出：{5}
提示：
	链表中节点数目为 n
	1 <= n <= 500
	-500 <= Node.val <= 500
	1 <= left <= right <= n
	进阶： 你可以使用一趟扫描完成反转吗？ */

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

class Solution {
public:
	ListNode *reverseBetween(ListNode *head, int left, int right) {
		ListNode dummy(0, head), *p = &dummy;
		for(int i = 1; i < left; ++i) p = p->next;
		ListNode *prev = nullptr, *curr = p->next;
		for(int i = left; i <= right; ++i) {
			ListNode *temp = curr->next;
			curr->next = prev;
			prev = curr;
			curr = temp;
		}
		p->next->next = curr;
		p->next = prev;
		return dummy.next;
	}
};

int main() {
	Solution sol;
	ListNode *head;
	int left, right;
	
	head = createList(vector<int>(1, 5)), left = 1, right = 1;
	cout << sol.reverseBetween(head, left, right) << endl;

	head = createList({ 1, 2, 3, 4, 5 }), left = 2, right = 4;
	cout << sol.reverseBetween(head, left, right) << endl;
}