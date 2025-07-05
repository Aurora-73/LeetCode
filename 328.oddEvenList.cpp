// Created: 2025-07-05
#include "MyListNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 328. 奇偶链表
给定单链表的头节点head，将所有索引为奇数的节点和索引为偶数的节点分别分组，
保持它们原有的相对顺序，然后把偶数索引节点分组连接到奇数索引节点分组之后，返回重新排序的链表。
第一个节点的索引被认为是 奇数， 第二个节点的索引为偶数，以此类推。
请注意，偶数组和奇数组内部的相对顺序应该与输入时保持一致。
你必须在O(1)的额外空间复杂度和O(n)的时间复杂度下解决这个问题。
示例 1:
	输入: head = {1,2,3,4,5}
	输出:{1,3,5,2,4}
示例 2:
	输入: head = {2,1,3,5,6,4,7}
	输出: {2,3,6,7,1,5,4}
提示:
	n == 链表中的节点数
	0 <= n <= 10^4
	-10^6<= Node.val <= 10^6 */

class Solution1 {
public:
	ListNode *oddEvenList(ListNode *head) {
		ListNode oddhead, evenhead;
		ListNode *oddNow = &oddhead, *evenNow = &evenhead, *now = head;
		while(now) {
			oddNow->next = now;
			oddNow = now;
			now = now->next;
			if(now) {
				evenNow->next = now;
				evenNow = now;
				now = now->next;
			}
		}
		oddNow->next = evenhead.next;
		evenNow->next = nullptr;
		return oddhead.next;
	}
};

class Solution {
public:
	ListNode *oddEvenList(ListNode *head) {
		if(!head || !head->next || !head->next->next) return head;
		ListNode *oddNow = head, *evenNow = head->next, *now = head->next->next;
		evenNow->next = nullptr;
		while(now) {
			ListNode *temp = now->next;
			now->next = oddNow->next;
			oddNow->next = now;
			oddNow = now;
			evenNow->next = temp;
			evenNow = temp;
			if(temp) {
				now = temp->next;
			} else {
				now = temp;
			}
		}
		return head;
	}
}; // 先把前两个取下来，这样就有了 oddNow 和 evenNow

int main() {
	Solution sol;
	ListNode *head;
	head = createList({ 1, 2, 3, 4, 5 });
	cout << sol.oddEvenList(head) << endl; // {1,3,5,2,4}
	head = createList({ 2, 1, 3, 5, 6, 4, 7 });
	cout << sol.oddEvenList(head) << endl; // {2,3,6,7,1,5,4}
}