// Created: 2025-04-28
#include "MyUtils.h"
#include "ListNode.h"

/*86. 分隔链表
给你一个链表的头节点 head 和一个特定值 x ，请你对链表进行分隔，使得所有 小于 x 的节点都出现在 大于或等于 x 的节点之前。
你应当 保留 两个分区中每个节点的初始相对位置。*/

class Solution1 {
public:
	ListNode *partition(ListNode *head, int x) {
		unique_ptr<ListNode> upper(new ListNode), lowwer(new ListNode);
		ListNode *ut = upper.get(), *lt = lowwer.get();
		while(head) {
			ListNode *temp = head->next;
			head->next = nullptr;
			if(head->val < x) {
				lt->next = head;
				lt = head;
			} else {
				ut->next = head;
				ut = head;
			}
			head = temp;
		}
		lt->next = upper->next;
		return lowwer->next;
	}
};

class Solution2 {
public:
	ListNode *partition(ListNode *head, int x) {
		unique_ptr<ListNode> res(new ListNode);
		ListNode *bound = res.get(), *tail = res.get();
		while(head) {
			auto temp = head->next;
			if(head->val < x) {
				head->next = bound->next;
				bound->next = head;
				if(bound == tail) {
					tail = head;
				}
				bound = head;
			} else {
				head->next = tail->next;
				tail->next = head;
				tail = head;
			}
			head = temp;
		}
		return res->next;
	}
};

int main() {
	ListNode *head = createList({ 9, 3, 5, 2, 6, 2, 3, 5, 0 });
	cout << head << endl;
	Solution1 sol1;
	head = sol1.partition(head, 3);
	cout << head << endl;
	deleteList(head);
	head = createList({ 9, 3, 5, 2, 6, 2, 3, 5, 0 });
	Solution2 sol2;
	head = sol2.partition(head, 3);
	cout << head << endl;
	deleteList(head);
}