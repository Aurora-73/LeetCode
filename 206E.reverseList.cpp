// Created: 2025-04-25
#include "MyListNode.h"
#include "MyUtils.hpp"

/* 给你单链表的头节点 head，请你反转链表，并返回反转后的链表。
示例 1：
	输入：head = {1,2,3,4,5}
	输出：{5,4,3,2,1}
示例 2：
	输入：head = {1,2}
	输出：{2,1}
示例 3：
	输入：head = {}
	输出：{}
提示：
	链表中节点的数目范围是 {0, 5000}
	-5000 <= Node.val <= 5000
	进阶：链表可以选用迭代或递归方式完成反转。你能否用两种方法解决这道题？ */

class Solution1 {
public:
	ListNode *reverseList(ListNode *head) {
		ListNode dummy, *headNode = &dummy;
		while(head) {
			ListNode *temp = head->next;
			head->next = headNode->next;
			headNode->next = head;
			head = temp;
		}
		return dummy.next;
	}
}; // 有头结点，尾插法

class Solution {
public:
	ListNode *reverseList(ListNode *head) {
		if(!head) return head;
		ListNode *prev = nullptr, *curr = head;
		while(curr) {
			ListNode *temp = curr->next;
			curr->next = prev;
			prev = curr;
			curr = temp;
		}
		return prev;
	}
}; // 无头结点，三指针反转

int main() {
	ListNode *head = createList(5);
	cout << head << endl;
	Solution1 sol1;
	head = sol1.reverseList(head);
	cout << head << endl;
	Solution sol;
	head = sol.reverseList(head);
	cout << head << endl;
	deleteList(head);
}