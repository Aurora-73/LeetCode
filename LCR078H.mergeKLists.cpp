// Created: 2025-12-13
#include "MyListNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个链表数组，每个链表都已经按升序排列。
请将所有链表合并到一个升序链表中，返回合并后的链表。
示例 1：
	输入：lists = {{1,4,5},{1,3,4},{2,6}}
	输出：{1,1,2,3,4,4,5,6}
	解释：链表数组如下：
	{
	  1->4->5,
	  1->3->4,
	  2->6
	}
	将它们合并到一个有序链表中得到。
	1->1->2->3->4->4->5->6
示例 2：
	输入：lists = {}
	输出：{}
示例 3：
	输入：lists = {{}}
	输出：{}
提示：
	k == lists.length
	0 <= k <= 10^4
	0 <= lists{i}.length <= 500
	-10^4 <= lists{i}{j} <= 10^4
	lists{i} 按 升序 排列
	lists{i}.length 的总和不超过 10^4 */

class Solution1 {
public:
	ListNode *mergeKLists(vector<ListNode *> &lists) {
		if(lists.empty()) return nullptr;
		unique_ptr<ListNode> dummy = make_unique<ListNode>();
		ListNode *tail = dummy.get();
		while(true) {
			int index = 0;
			for(int i = 1; i < lists.size(); ++i) {
				if(!lists[index] || (lists[i] && (lists[i]->val < lists[index]->val))) {
					index = i;
				}
			}
			if(!lists[index]) {
				tail->next = nullptr;
				return dummy->next;
			}
			tail->next = lists[index];
			tail = tail->next;
			lists[index] = lists[index]->next;
		}
	}
}; // 可以用优先队列优化

class Solution2 {
public:
	ListNode *mergeKLists(vector<ListNode *> &lists) {
		if(lists.empty()) return nullptr;
		unique_ptr<ListNode> dummy = make_unique<ListNode>();
		ListNode *tail = dummy.get();
		auto cmp = [&](int l, int r) {
			return lists[l]->val > lists[r]->val;
		};
		priority_queue<int, vector<int>, decltype(cmp)> pq(cmp); // 只能入队非空元素
		for(int i = 0; i < lists.size(); ++i) {
			if(lists[i]) {
				pq.push(i);
			}
		}
		while(!pq.empty()) {
			int index = pq.top();
			pq.pop();
			tail->next = lists[index];
			tail = tail->next;
			lists[index] = lists[index]->next;
			if(lists[index]) pq.push(index);
		}
		tail->next = nullptr;
		return dummy->next;
	}
}; // 可以用优先队列优化

class Solution3 {
public:
	ListNode *mergeKLists(vector<ListNode *> &lists) {
		auto cmp = [](ListNode *l, ListNode *r) {
			return l->val > r->val;
		};
		priority_queue<ListNode *, vector<ListNode *>, decltype(cmp)> pq(cmp);
		for(auto node : lists) {
			if(node) pq.push(node);
		}
		ListNode head, *tail = &head;
		while(!pq.empty()) {
			tail->next = pq.top();
			tail = tail->next;
			pq.pop();
			if(tail->next) pq.push(tail->next);
		}
		return head.next;
	}
}; // 优先队列的优化：在第一次遍历后可以直接丢弃lists，直接从pq里面取值

class Solution {
public:
	ListNode *mergeKLists(vector<ListNode *> &lists) {
		if(!lists.size()) return nullptr;
		for(size_t subLen = 1; subLen < lists.size(); subLen *= 2) {
			for(size_t i = 0; i + subLen < lists.size(); i += 2 * subLen) {
				lists[i] = merge(lists[i], lists[i + subLen]);
			}
		}
		return lists[0];
	}

private:
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
	vector<ListNode *> lists;
	lists = { createList({ 1, 4, 5 }), createList({ 1, 3, 4 }), createList({ 2, 6 }) };
	cout << sol.mergeKLists(lists) << endl;
	lists = {};
	cout << sol.mergeKLists(lists) << endl;
	lists = { {} };
	cout << sol.mergeKLists(lists) << endl;
}