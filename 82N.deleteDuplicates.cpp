// Created: 2026-01-23
#include "MyListNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个已排序的链表的头head，删除原始链表中所有重复数字的节点，只留下不同的数字。
返回 已排序的链表。
示例 1：
	输入：head = {1,2,3,3,4,4,5}
	输出：{1,2,5}
示例 2：
	输入：head = {1,1,1,2,3}
	输出：{2,3}
提示：
	链表中节点数目在范围 {0, 300} 内
	-100 <= Node.val <= 100
	题目数据保证链表已经按升序 排列 */

class Solution1 {
public:
	ListNode *deleteDuplicates(ListNode *head) {
		ListNode headNode(-1, head);
		ListNode *left = &headNode, *right = head;
		int count = 0;
		while(right) {
			while(right && right->val == left->next->val) {
				right = right->next;
				count++;
			} // right已经指向第一个未判断的元素了，不需要进行后移了
			if(count > 1) {
				ListNode *temp1 = left->next, *temp2;
				left->next = right;
				while(temp1 != right) {
					temp2 = temp1->next;
					delete temp1;
					temp1 = temp2;
				}
			} else {
				left = left->next;
			} // 如果去除过元素，left就已经指向未判断元素的前一个元素了，不需要移动，否则需要后移一位
			count = 0;
		}
		return headNode.next;
	}
};

class Solution2 {
public:
	ListNode *deleteDuplicates(ListNode *head) {
		if(!head || !head->next) return head;

		// 情况1：当前节点是重复段的开始
		if(head->val == head->next->val) {
			int dupVal = head->val;
			// 跳过所有等于 dupVal 的节点
			while(head && head->val == dupVal) {
				head = head->next;
			}
			// 从第一个不同值的位置继续递归
			return deleteDuplicates(head);
		}
		// 情况2：当前节点是唯一值
		else {
			head->next = deleteDuplicates(head->next);
			return head;
		}
	}
};

class Solution {
public:
	ListNode *deleteDuplicates(ListNode *head) {
		ListNode dummy, *p = head, *tail = &dummy;
		while(p) {
			if(p->next && p->val == p->next->val) {
				int dupVal = p->val;
				while(p && p->val == dupVal) {
					ListNode *temp = p;
					p = p->next;
					delete temp;
				}
			} else {
				tail->next = p;
				tail = tail->next;
				p = p->next;
			}
		}
		tail->next = nullptr; // 记得断尾
		return dummy.next;
	}
};

int main() {
	Solution sol;
	ListNode *head;
	head = createList({ 1, 2, 2 });
	cout << sol.deleteDuplicates(head) << endl; // { 1 }

	head = createList({ 1, 2, 3, 3, 4, 4, 5 });
	cout << sol.deleteDuplicates(head) << endl; // { 1 -> 2 -> 5 }

	head = createList({ 1, 1, 1, 2, 3 });
	cout << sol.deleteDuplicates(head) << endl; // { 2 -> 3 }
}