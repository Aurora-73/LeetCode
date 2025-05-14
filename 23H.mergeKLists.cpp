// Created: 2025-05-13
#include "MyUtils.h"
#include "MyListNode.h"

/*23. 合并 K 个升序链表
给你一个链表数组，每个链表都已经按升序排列。
请你将所有链表合并到一个升序链表中，返回合并后的链表。
示例 1：
输入：lists = [[1,4,5],[1,3,4],[2,6]]
输出：[1,1,2,3,4,4,5,6]
解释：链表数组如下：
1->4->5,
1->3->4,
2->6
将它们合并到一个有序链表中得到。
1->1->2->3->4->4->5->6*/

class Solution {
public:
	ListNode *mergeKLists(vector<ListNode *> &lists) {
		if(!lists.size())
			return nullptr;
		for(size_t subLen = 1; subLen < lists.size(); subLen *= 2) {
			for(size_t i = 0; i + subLen < lists.size(); i += 2 * subLen) {
				lists[i] = merge(lists[i], lists[i + subLen]);
			}
		}
		return lists[0];
	}
	ListNode *merge(ListNode *list1, ListNode *list2) {
		if(!list1 || !list2) {
			return list1 ? list1 : list2;
		}
		ListNode *head, *tail;
		if(list1->val < list2->val) {
			head = list1;
			list1 = list1->next;
		} else {
			head = list2;
			list2 = list2->next;
		}
		tail = head;
		while(list1 && list2) {
			if(list1->val < list2->val) {
				tail->next = list1;
				list1 = list1->next;
			} else {
				tail->next = list2;
				list2 = list2->next;
			}
			tail = tail->next;
		}
		tail->next = list1 ? list1 : list2;
		return head;
	}
};

int main() {
	Solution sol;
	vector<ListNode *> lists { createList({ 1, 4, 5 }), createList({ 1, 3, 4 }), createList({ 2, 6 }) };
	cout << sol.mergeKLists(lists);
}