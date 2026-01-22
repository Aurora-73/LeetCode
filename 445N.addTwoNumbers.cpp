// Created: 2026-01-22
#include "MyListNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给你两个 非空 链表来代表两个非负整数。
数字最高位位于链表开始位置。它们的每个节点只存储一位数字。将这两数相加会返回一个新的链表。
你可以假设除了数字 0 之外，这两个数字都不会以零开头。
示例1：
	输入：l1 = {7,2,4,3}, l2 = {5,6,4}
	输出：{7,8,0,7}
示例2：
	输入：l1 = {2,4,3}, l2 = {5,6,4}
	输出：{8,0,7}
示例3：
	输入：l1 = {0}, l2 = {0}
	输出：{0}
提示：
	链表的长度范围为 {1, 100}
	0 <= node.val <= 9
	输入数据保证链表代表的数字无前导 0
	进阶：如果输入链表不能翻转该如何解决？ */

class Solution {
public:
	ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
		l1 = reverse(l1), l2 = reverse(l2);
		ListNode dummy, *tail = &dummy;
		int up = 0;
		while((l1 && l2) || up) {
			if(l1) {
				up += l1->val;
				l1 = l1->next;
			}
			if(l2) {
				up += l2->val;
				l2 = l2->next;
			}
			tail->next = new ListNode(up % 10);
			tail = tail->next;
			up /= 10;
		}
		if(l1) tail->next = l1;
		if(l2) tail->next = l2;
		return reverse(dummy.next);
	}

private:
	ListNode *reverse(ListNode *list) {
		ListNode *prev = nullptr, *temp;
		while(list) {
			temp = list->next;
			list->next = prev;
			prev = list;
			list = temp;
		}
		return prev;
	}
};

int main() {
	Solution sol;
	ListNode *l1, *l2;
	l1 = createList({ 7, 2, 4, 3 }), l2 = createList({ 5, 6, 4 });
	cout << sol.addTwoNumbers(l1, l2) << endl;

	l1 = createList({ 2, 4, 3 }), l2 = createList({ 5, 6, 4 });
	cout << sol.addTwoNumbers(l1, l2) << endl;

	l1 = createList({ 0 }), l2 = createList({ 0 });
	cout << sol.addTwoNumbers(l1, l2) << endl;
}