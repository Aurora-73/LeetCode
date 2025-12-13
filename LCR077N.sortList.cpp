// Created: 2025-12-13
#include "MyListNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定链表的头结点head，请将其按 升序 排列并返回 排序后的链表。
示例 1：
	输入：head = {4,2,1,3}
	输出：{1,2,3,4}
示例 2：
	输入：head = {-1,5,3,4,0}
	输出：{-1,0,3,4,5}
示例 3：
	输入：head = {}
	输出：{}
提示：
	链表中节点的数目在范围{0, 5 * 10^4}内
	-10^5<= Node.val <= 10^5
	进阶：你可以在O(nlogn) 时间复杂度和常数级空间复杂度下，对链表进行排序吗？
注意：本题与主站 148题相同： */

class Solution1 {
public:
	ListNode *sortList(ListNode *head) {
		if(!head || !head->next) return head;
		ListNode *fast = head->next, *slow = head;
		while(fast && fast->next) {
			fast = fast->next->next;
			slow = slow->next;
		}
		ListNode *left = head, *right = slow->next;
		slow->next = nullptr;
		left = sortList(left);
		right = sortList(right);
		// 注意这里的递归返回值需要保留，因为排序后新的头不一定原本的那个
		return merge(left, right);
	}

private:
	ListNode *merge(ListNode *a, ListNode *b) {
		if(!a || !b) return a ? a : b;
		ListNode *head, *tail;
		if(a->val <= b->val) {
			head = a;
			tail = a;
			a = a->next;
		} else {
			head = b;
			tail = b;
			b = b->next;
		}
		while(a && b) {
			if(a->val <= b->val) {
				tail->next = a;
				a = a->next;
				tail = tail->next;
			} else {
				tail->next = b;
				b = b->next;
				tail = tail->next;
			}
		}
		tail->next = a ? a : b;
		return head;
	}
}; // 自顶向下的归并排序，空间复杂度O(n)

class Solution2 {
public:
	ListNode *sortList(ListNode *head) {
		if(!head || !head->next) return head;

		// 1. 计算链表长度
		int n = 0;
		for(ListNode *p = head; p; p = p->next) n++;

		ListNode dummy;
		dummy.next = head;

		// 2. step = 子链表长度：1, 2, 4, 8 ...
		for(int step = 1; step < n; step <<= 1) {
			ListNode *prev = &dummy;
			ListNode *curr = dummy.next;

			while(curr) {
				// 3. 切出左链表
				ListNode *left = curr;
				ListNode *right = split(left, step);
				curr = split(right, step);

				// 4. 合并并接回
				prev->next = merge(left, right);
				while(prev->next) prev = prev->next;
			}
		}
		return dummy.next;
	}

private:
	// 将 head 开始的链表切成长度为 step 的一段，返回剩余部分的头
	ListNode *split(ListNode *head, int step) {
		while(--step && head) {
			head = head->next;
		}
		if(!head) return nullptr;
		ListNode *next = head->next;
		head->next = nullptr;
		return next;
	}

	// 合并两个有序链表，同上
	ListNode *merge(ListNode *a, ListNode *b) {
		if(!a) return b;
		if(!b) return a;

		ListNode *head;
		if(a->val <= b->val) {
			head = a;
			a = a->next;
		} else {
			head = b;
			b = b->next;
		}

		ListNode *tail = head;
		while(a && b) {
			if(a->val <= b->val) {
				tail = tail->next = a;
				a = a->next;
			} else {
				tail = tail->next = b;
				b = b->next;
			}
		}
		tail->next = a ? a : b;
		return head;
	}
}; // 自底向上的归并排序，空间复杂度O(1)
// 注意：prev指向已排序部分的最后一个，curr指向还没处理的链表的头

class Solution {
public:
	ListNode *sortList(ListNode *head) {
		int n = 0;
		for(auto p = head; p != nullptr; p = p->next) ++n;
		ListNode dummy(0, head);

		for(int step = 1; step < n; step <<= 1) {
			ListNode *prev = &dummy;     // prev指向已排序部分的最后一个
			ListNode *curr = dummy.next; // curr指向还没处理的链表的头

			while(curr) {
				ListNode *left = curr, *right = nullptr; // right赋默认值，防止不修改
				ListNode *next = nullptr;                // next指向下一轮 while 要处理的起点
				// 此时curr已经没用了，可以移动curr，而且curr本身就是未处理部分的链表头
				for(int i = 1; i < step && curr->next; ++i, curr = curr->next);
				right = curr->next;
				curr->next = nullptr;
				curr = right;
				if(curr) {
					for(int i = 1; i < step && curr->next; ++i, curr = curr->next);
					next = curr->next;
					curr->next = nullptr;
				}
				curr = next; // 不能放到if里面，否则不会更新curr
				auto [h, t] = merge(left, right);
				prev->next = h;
				prev = t;
			}
		}
		return dummy.next;
	}

private:
	// 合并两个有序链表，同上
	pair<ListNode *, ListNode *> merge(ListNode *a, ListNode *b) {
		if(!a) swap(a, b); // 保证a是最有可能不为空的
		if(!b) {
			for(b = a; b && b->next; b = b->next);
			return { a, b };
		}

		ListNode *head;
		if(a->val <= b->val) {
			head = a;
			a = a->next;
		} else {
			head = b;
			b = b->next;
		}

		ListNode *tail = head;
		while(a && b) {
			if(a->val <= b->val) {
				tail = tail->next = a;
				a = a->next;
			} else {
				tail = tail->next = b;
				b = b->next;
			}
		}
		tail->next = a ? a : b;
		while(tail && tail->next) tail = tail->next;
		return { head, tail };
	}
}; // 注意：prev指向已排序部分的最后一个，curr指向还没处理的链表的头

int main() {
	Solution sol;
	ListNode *head;
	head = createList({ 4, 2, 1, 3 });
	cout << sol.sortList(head) << endl;
	head = createList({ -1, 5, 3, 4, 0 });
	cout << sol.sortList(head) << endl;
}