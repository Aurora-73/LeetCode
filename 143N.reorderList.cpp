// Created: 2026-01-21
#include "MyListNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个单链表 L 的头节点 head，单链表 L 表示为：
L0 → L1 → … → Ln - 1 → Ln
请将其重新排列后变为：
L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
示例 1：
	输入：head = {1,2,3,4}
	输出：{1,4,2,3}
示例 2：
	输入：head = {1,2,3,4,5}
	输出：{1,5,2,4,3}
提示：
	链表的长度范围为 {1, 5 * 10^4}
	1 <= node.val <= 1000 */

class Solution {
public:
	void reorderList(ListNode *head) {
		ListNode *slow = head, *fast = head;
		while(fast && fast->next) {
			fast = fast->next->next;
			slow = slow->next;
		}
		// 寻找中点完成，slow 指向前半段的尾节点

		ListNode *prev = nullptr, *curr = slow->next;
		slow->next = nullptr;
		while(curr) {
			ListNode *temp = curr->next;
			curr->next = prev;
			prev = curr;
			curr = temp;
		}
		// 后半段转置完成，prev 是链头

		fast = head, slow = prev;
		while(slow) {
			ListNode *temp = slow;
			slow = slow->next;
			temp->next = fast->next;
			fast->next = temp;
			fast = fast->next->next;
		}
		// 穿插链表，要求：后半段长度 ≤ 前半段长度
	}
};

int main() {
	Solution sol;
	ListNode *head;
	head = createList({ 1, 2, 3, 4 });
	sol.reorderList(head);
	cout << head << endl;

	head = createList({ 1, 2, 3, 4, 5 });
	sol.reorderList(head);
	cout << head << endl;
}