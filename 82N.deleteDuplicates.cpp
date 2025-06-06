// Created: 2025-04-28
#include "MyListNode.h"
#include "MyUtils.hpp"
/*给定一个已排序的链表的头 head ， 删除原始链表中所有重复数字的节点，只留下不同的数字 。返回 已排序的链表， 不是去重，是只要多余一个都删掉*/

class Solution {
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

int main() {
	ListNode *head = createList({ 1, 1, 2, 2, 4, 6, 7, 7, 8 });
	cout << head << endl;
	Solution sol;
	head = sol.deleteDuplicates(head);
	cout << head << endl;
	deleteList(head);
}