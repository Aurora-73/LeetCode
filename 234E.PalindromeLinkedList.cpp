// Created: 2025-06-14
#include "MyDateGen.h"
#include "MyListNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 234. 回文链表
给你一个单链表的头节点 head，请你判断该链表是否为回文链表。
如果是，返回 true ；否则，返回 false。
示例 1：
	输入：head = {1,2,2,1}
	输出：true
示例 2：
	输入：head = {1,2}
	输出：false
提示：
	链表中节点数目在范围{1, 10^5} 内
	0 <= Node.val <= 9
	进阶：你能否用O(n) 时间复杂度和 O(1) 空间复杂度解决此题？ */

class Solution1 {
public:
	bool isPalindrome(ListNode *head) {
		if(!head->next) return true;
		vector<int> vals;
		ListNode *fast = head, *slow = head;
		while(fast && fast->next) {
			vals.push_back(slow->val);
			slow = slow->next;
			fast = fast->next->next;
		}
		// 如果是奇数长度，跳过中间节点
		if(fast) slow = slow->next;
		for(auto it = vals.rbegin(); it != vals.rend(); ++it) {
			if(*it != slow->val) return false;
			slow = slow->next;
		}
		return true;
	}
};

class Solution {
public:
	bool isPalindrome(ListNode *head) {
		if(!head->next) {
			return true;
		}
		ListNode *fast = head->next, *slow = head;
		while(fast && fast->next) {
			fast = fast->next->next;
			slow = slow->next;
		} // slow 的下一个是中间
		ListNode *p = slow->next;
		slow->next = nullptr;
		while(p) {
			ListNode *temp = p->next;
			p->next = slow->next;
			slow->next = p;
			p = temp;
		}
		slow = slow->next;
		while(slow) {
			if(slow->val != head->val) {
				return false;
			}
			slow = slow->next;
			head = head->next;
		}
		return true;
	}
};
/* 找链表中点
    如果偶数长度时想取 右中点，就 fast = head;。
    如果想取 左中点，就 fast = head->next; 
环形链表（判环／找环入口）
    一定要让 slow = head; fast = head;
    并且用「先移动再判断是否相遇」的方式。这样逻辑最简洁、最不容易出错。*/

int main() {
	Solution sol;
	ListNode *head;

	head = createList({ 1, 2, 2, 1 });
	cout << sol.isPalindrome(head) << endl;

	head = createList({ 1, 2 });
	cout << sol.isPalindrome(head) << endl;

	head = createList({ 3, 0, 1, 0, 5, 3, 0, 1, 0, 5 });
	cout << sol.isPalindrome(head) << endl;
}