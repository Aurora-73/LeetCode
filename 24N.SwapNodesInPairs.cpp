// Created: 2025-06-14
#include "MyDateGen.h"
#include "MyListNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 24. 两两交换链表中的节点
给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。
你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。
示例 1：
	输入：head = {1,2,3,4}
	输出：{2,1,4,3}
示例 2：
	输入：head = {}
	输出：{}
示例 3：
	输入：head = {1}
	输出：{1}
提示：
	链表中节点的数目在范围 {0, 100} 内
	0 <= Node.val <= 100 */

class Solution {
public:
	ListNode *swapPairs(ListNode *head) {
		if(!head || !head->next) {
			return head;
		}
		ListNode *next = head->next, *temp, *prev = nullptr, *newHead = head->next;
		while(next) {
			temp = next->next;
			if(prev) prev->next = next;
			prev = head;
			next->next = head;
			head->next = temp;
			head = head->next;
			next = head ? head->next : nullptr;
		}
		return newHead;
	}
};

int main() {
	Solution sol;
	ListNode *head;
	head = createList({ 1, 2, 3, 4 });
	cout << sol.swapPairs(head) << endl;
	head = createList({});
	cout << sol.swapPairs(head) << endl;
	head = createList({ 1 });
	cout << sol.swapPairs(head) << endl;
}