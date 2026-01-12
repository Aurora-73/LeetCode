// Created: 2025-04-28
#include "MyListNode.h"
#include "MyUtils.hpp"
/*  25. K 个一组翻转链表
给你链表的头节点 head ，每 k 个节点一组进行翻转，请你返回修改后的链表。
k 是一个正整数，它的值小于或等于链表的长度。如果节点总数不是 k 的整数倍，那么请将最后剩余的节点保持原有顺序。
你不能只是单纯的改变节点内部的值，而是需要实际进行节点交换。*/

class Solution1 {
public:
	ListNode *reverseKGroup(ListNode *head, int k) {
		ListNode headNode(-1, head);
		ListNode *left = &headNode, *right = &headNode, *next;
		while(right) {
			for(int i = 0; i < k && right; i++) {
				right = right->next;
			}
			if(!right) break;
			next = right->next;
			right->next = nullptr;
			right = left->next;
			reverseListAfterHead(left);
			left = right;
			left->next = next;
		}
		return headNode.next;
	}
	ListNode *reverseListAfterHead(ListNode *head) {
		ListNode *now = head->next;
		head->next = nullptr;
		while(now) {
			ListNode *temp = now->next;
			now->next = head->next;
			head->next = now;
			now = temp;
		}
		return head;
	}
};

class Solution2 {
public:
	ListNode *reverseKGroup(ListNode *head, int k) {
		ListNode dummy(0, head);
		ListNode *pre = &dummy;

		while(true) {
			// 1. 找到这一组的第 k 个节点
			ListNode *kth = pre;
			for(int i = 0; i < k && kth; ++i) {
				kth = kth->next;
			}
			if(!kth) break;

			// 2. 记录下一组的起点
			ListNode *nxt = kth->next;

			// 3. 原地反转 [pre->next, kth]
			ListNode *prev = nxt;
			ListNode *cur = pre->next;
			while(cur != nxt) {
				ListNode *tmp = cur->next;
				cur->next = prev;
				prev = cur;
				cur = tmp;
			}

			// 4. 接回去
			ListNode *oldHead = pre->next;
			pre->next = kth;
			pre = oldHead;
		}
		return dummy.next;
	}
};

class Solution {
public:
	ListNode *reverseKGroup(ListNode *head, int k) {
		ListNode dummy(-1, head), *curr = &dummy;
		while(curr && curr->next) {
			ListNode *p = curr, *temp = nullptr;
			for(int i = 0; i < k && p; ++i) p = p->next;
			if(p) {
				temp = p->next;
				p->next = nullptr;
			} else {
				break;
			}
			auto [beg, end] = reverse(curr->next);
			curr->next = beg;
			end->next = temp;
			curr = end;
		}
		return dummy.next;
	}

private:
	pair<ListNode *, ListNode *> reverse(ListNode *head) {
		ListNode *prev = nullptr, *curr = head;
		while(curr) {
			ListNode *temp = curr->next;
			curr->next = prev;
			prev = curr;
			curr = temp;
		}
		return { prev, head };
	}
};

int main() {
	ListNode *head = createList(20);
	cout << head << endl;
	Solution sol1;
	head = sol1.reverseKGroup(head, 4);
	cout << head << endl;
	deleteList(head);
}