// Created: 2025-12-24
#include "MyListNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 面试题 02.04. 分割链表
给你一个链表的头节点 head 和一个特定值 x，请你对链表进行分隔，
使得所有 小于 x 的节点都出现在 大于或等于 x 的节点之前。
你不需要 保留 每个分区中各节点的初始相对位置。
示例 1：
	输入：head = {1,4,3,2,5,2}, x = 3
	输出：{1,2,2,4,3,5}
示例 2：
	输入：head = {2,1}, x = 2
	输出：{1,2}
提示：
	链表中节点的数目在范围 {0, 200} 内
	-100 <= Node.val <= 100
	-200 <= x <= 200 */

class Solution1 {
public:
	ListNode *partition(ListNode *head, int x) {
		if(!head || !head->next) return head;
		ListNode *part, *curr = head->next;
		if(head->val < x) {
			part = head->next;
		} else {
			part = head;
		}
		while(curr) {
			if(curr->val < x) {
				swap(part->val, curr->val);
				part = part->next;
			}
			curr = curr->next;
		}
		return head;
	}
};

class Solution {
public:
	ListNode *partition(ListNode *head, int x) {
		if(!head || !head->next) return head;
		ListNode smaller, bigger;
		ListNode *smallerTail = &smaller, *biggerTail = &bigger;
		while(head) {
			if(head->val < x) {
				smallerTail->next = head;
				smallerTail = head;
			} else {
				biggerTail->next = head;
				biggerTail = head;
			}
			head = head->next;
		}
		smallerTail->next = bigger.next;
		biggerTail->next = nullptr;
		return smaller.next;
	}
};

int main() {
	Solution sol;
	ListNode *head;
	int x;
	head = createList({ 1, 4, 3, 2, 5, 2 }), x = 3;
	cout << sol.partition(head, x) << endl;

	head = createList({ 2, 1 }), x = 2;
	cout << sol.partition(head, x) << endl;
}