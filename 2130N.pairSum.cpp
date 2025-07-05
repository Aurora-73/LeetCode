// Created: 2025-07-05
#include "MyListNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 2130. 链表最大孪生和
在一个大小为n且 n为偶数 的链表中，对于0 <= i <= (n / 2) - 1的 i，
第i个节点（下标从 0开始）的孪生节点为第(n-1-i)个节点。
	比方说，n = 4那么节点0是节点 3的孪生节点，节点 1是节点 2的孪生节点。这是长度为 n = 4的链表中所有的孪生节点。
孪生和定义为一个节点和它孪生节点两者值之和。
给你一个长度为偶数的链表的头节点head，请你返回链表的 最大孪生和。
示例1：
    输入：head = {5,4,2,1}
    输出：6
    解释：
    节点 0 和节点 1 分别是节点 3 和 2 的孪生节点。孪生和都为 6。
    链表中没有其他孪生节点。
    所以，链表的最大孪生和是 6。
示例 2：
	输入：head = {4,2,2,3}
	输出：7
	解释：
	链表中的孪生节点为：
	- 节点 0 是节点 3 的孪生节点，孪生和为 4 + 3 = 7。
	- 节点 1 是节点 2 的孪生节点，孪生和为 2 + 2 = 4。
	所以，最大孪生和为 max(7, 4) = 7。
示例 3：
	输入：head = {1,100000}
	输出：100001
	解释：
	链表中只有一对孪生节点，孪生和为 1 + 100000 = 100001。
提示：
	链表的节点数目是{2, 10^5}中的偶数。
	1 <= Node.val <= 10^5 */

class Solution1 {
public:
	int pairSum(ListNode *head) {
		int n = 0, res = INT_MIN;
		ListNode *p = head;
		while(p) {
			++n;
			p = p->next;
		}
		n /= 2;
		vector<int> vals;
		vals.reserve(n);
		p = head;
		for(int i = 0; i < n; ++i) {
			vals.push_back(p->val);
			p = p->next;
		}
		for(int i = 0; i < n; ++i) {
			res = max(res, vals[n - i - 1] + p->val);
			p = p->next;
		}
		return res;
	}
}; // 记录数组元素，然后进行加和

class Solution {
public:
	int pairSum(ListNode *head) {
		ListNode *fast = head->next, *slow = head;
		while(fast && fast->next) {
			fast = fast->next->next;
			slow = slow->next;
		}
		fast = slow->next;
		slow->next = nullptr;
		while(fast) {
			auto temp = fast->next;
			fast->next = slow->next;
			slow->next = fast;
			fast = temp;
		}
		fast = head, slow = slow->next;
		int res = INT_MIN;
		while(slow) {
			res = max(res, fast->val + slow->val);
			slow = slow->next;
			fast = fast->next;
		}
		return res;
	}
}; // 翻转后半段，然后加和前半段和后半段

int main() {
	Solution sol;
	ListNode *head;
	head = createList({ 5, 4, 2, 1 });
	cout << sol.pairSum(head) << endl; // 6
	head = createList({ 4, 2, 2, 3 });
	cout << sol.pairSum(head) << endl; // 7
	head = createList({ 1, 100000 });
	cout << sol.pairSum(head) << endl; // 100001
}