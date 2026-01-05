// Created: 2025-12-24
#include "MyListNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定两个用链表表示的整数，每个节点包含一个数位。
这些数位是反向存放的，也就是个位排在链表首部。
编写函数对这两个整数求和，并用链表形式返回结果。
示例：
输入：(7 -> 1 -> 6) + (5 -> 9 -> 2)，即617 + 295
输出：2 -> 1 -> 9，即912
进阶：思考一下，假设这些数位是正向存放的，又该如何解决呢?*/

class Solution1 {
public:
	ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
		bool up = false;
		ListNode dummy, *tail = &dummy;
		while(l1 && l2) {
			int sum = up + l1->val + l2->val;
			if(sum > 9) {
				sum %= 10;
				up = true;
			} else {
				up = false;
			}
			tail->next = new ListNode(sum);
			tail = tail->next;
			l1 = l1->next;
			l2 = l2->next;
		}
		if((l1 || l2) && up) {
			if(l2) swap(l1, l2);
			while(up) {
				int sum = up + l1->val;
				if(sum > 9) {
					sum %= 10;
					up = true;
				} else {
					up = false;
				}
				tail->next = new ListNode(sum);
				tail = tail->next;
				l1 = l1->next;
				if(!l1) break;
			}
		}
		if((l1 || l2) && !up) {
			tail->next = l1 ? l1 : l2;
		}
		if(up) {
			tail->next = new ListNode(1);
		}
		return dummy.next;
	}
};

class Solution {
public:
	ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
		ListNode dummy, *tail = &dummy;
		int carry = 0;
		while(l1 || l2 || carry) {
			int sum = carry;
			if(l1) {
				sum += l1->val;
				l1 = l1->next;
			}
			if(l2) {
				sum += l2->val;
				l2 = l2->next;
			}
			carry = sum / 10;
			tail->next = new ListNode(sum % 10);
			tail = tail->next;
		}
		return dummy.next;
	}
};

int main() {
	Solution sol;
	ListNode *l1, *l2;

	l1 = new ListNode(9), l2 = createList({ 1, 9, 9, 9, 9, 9, 8, 9, 9, 9 });
	cout << sol.addTwoNumbers(l1, l2) << endl;

	l1 = new ListNode(1), l2 = createList({ 9, 9 });
	cout << sol.addTwoNumbers(l1, l2) << endl;

	l1 = createList({ 7, 1, 6 });
	l2 = createList({ 5, 9, 2 });
	cout << sol.addTwoNumbers(l1, l2) << endl;

	l1 = createList({ 6, 1, 7 });
	l2 = createList({ 2, 9, 5 });
	cout << sol.addTwoNumbers(l1, l2) << endl;
}