// Created: 2025-05-13
#include "MyListNode.h"
#include "MyUtils.hpp"

/*148. 排序链表
给你链表的头结点 head ，请将其按 升序 排列并返回 排序后的链表 。*/

class Solution1 {
public:
	ListNode *sortList(ListNode *head) {
		ListNode dummy(numeric_limits<int>::min(), nullptr);
		while(head) {
			auto temp = head->next, find = &dummy;
			while(find->next && find->next->val < head->val) {
				find = find->next;
			}
			head->next = find->next;
			find->next = head;
			head = temp;
		}
		return dummy.next;
	}
}; // 插入排序，时间复杂度 O(n ^ 2)

class Solution {
public:
	ListNode *sortList(ListNode *head) {
		if(!head || !head->next) {
			return head;
		}
		ListNode *slow = head, *fast = head->next;
		while(fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
		}
		ListNode *l = sortList(slow->next);
		slow->next = nullptr;
		ListNode *r = sortList(head);
		return merge(l, r);
	}

private:
	ListNode *merge(ListNode *l, ListNode *r) {
		if(!l || !r) {
			return l ? l : r;
		}
		ListNode dummy, *tile = &dummy;
		while(l && r) {
			if(l->val < r->val) {
				tile->next = l;
				l = l->next;
			} else {
				tile->next = r;
				r = r->next;
			}
			tile = tile->next;
		}
		tile->next = l ? l : r;
		return dummy.next;
	}
}; // 3) 自顶向下归并

class Solution3 {
public:
	ListNode *sortList(ListNode *head) {
		if(!head || !head->next) return head;

		// 1) 计算总长度
		int length = 0;
		for(auto p = head; p; p = p->next) ++length;

		// 2) 哨兵节点
		ListNode dummy(0);
		dummy.next = head;

		// 3) 自底向上归并
		for(int subLen = 1; subLen < length; subLen <<= 1) {
			ListNode *prev = &dummy;
			ListNode *curr = dummy.next;
			while(curr) {
				ListNode *head1 = curr;
				ListNode *head2 = split(head1, subLen);
				curr = split(head2, subLen);
				auto mergePair = merge(head1, head2); // 同时获取归并的头和尾
				prev->next = mergePair.first;
				prev = mergePair.second;
			}
		}
		return dummy.next;
	}

private:
	// 切分：从 head 切出长度为 n 的子链并断开，返回剩下部分头
	ListNode *split(ListNode *head, int n) {
		for(int i = 1; head && i < n; ++i) {
			head = head->next;
		}
		if(!head) return nullptr;
		ListNode *second = head->next;
		head->next = nullptr;
		return second;
	}

	// 合并并同时返回尾节点
	pair<ListNode *, ListNode *> merge(ListNode *list1, ListNode *list2) {
		if(!list1 && !list2) {
			return { nullptr, nullptr };
		}
		ListNode *head, *tail;
		if(!list1 || !list2) {
			head = tail = list1 ? list1 : list2;
			while(tail->next) {
				tail = tail->next;
			}
			return { head, tail };
		}
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
		while(tail->next) {
			tail = tail->next;
		}
		return { head, tail };
	}
};
/* 找链表中点
    如果偶数长度时想取 右中点，就 fast = head;。
    如果想取 左中点，就 fast = head->next; 
环形链表（判环／找环入口）
    一定要让 slow = head; fast = head;
    并且用「先移动再判断是否相遇」的方式。这样逻辑最简洁、最不容易出错。*/

int main() {
	Solution1 sol1;
}