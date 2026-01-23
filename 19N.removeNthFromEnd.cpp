// Created: 2025-04-25
#include "MyListNode.h"
#include "MyUtils.hpp"

/*  19. 删除链表的倒数第 N 个结点
给你一个链表，删除链表的倒数第n个结点，并且返回链表的头结点。
示例 1：
	输入：head = {1,2,3,4,5}, n = 2
	输出：{1,2,3,5}
示例 2：
	输入：head = {1}, n = 1
	输出：{}
示例 3：
	输入：head = {1,2}, n = 1
	输出：{1}
提示：
	链表中结点的数目为 sz
	1 <= sz <= 30
	0 <= Node.val <= 100
	1 <= n <= sz
进阶：你能尝试使用一趟扫描实现吗？*/

class Solution1 {
public:
	ListNode *removeNthFromEnd(ListNode *head, int n) {
		ListNode headNode(0, head);
		ListNode *fast = &headNode, *slow = &headNode;
		for(int i = 0; i < n + 1; ++i) {
			fast = fast->next;
		}
		while(fast) {
			slow = slow->next;
			fast = fast->next;
		}
		ListNode *temp = slow->next;
		slow->next = slow->next->next;
		delete temp;
		return headNode.next;
	}
};
// 要找倒数第 n 个节点的前一个节点，实际上是找倒数第 n+1 个节点，而不是倒数第 n-1 个节点
// 由于最后fast为空，因此fast先走 a 步，则最后slow是在倒数第 a个节点
// 最终的判断条件是fast为空，因此这与是否有头结点无关，只要两者的出发位置是一样的
// 所以应该先让fast走 n+1 步

class Solution {
public:
	ListNode *removeNthFromEnd(ListNode *head, int n) {
		ListNode dummy(0, head), *fast = &dummy, *slow = &dummy;
		for(int i = 0; i < n; ++i) {
			fast = fast->next;
		}
		while(fast->next) {
			fast = fast->next;
			slow = slow->next;
		}
		slow->next = slow->next->next;
		return dummy.next;
	}
};

int main() {
	Solution sol;
	ListNode *head;
	int n;

	head = createList({ 1, 2, 3, 4, 5 }), n = 2;
	cout << sol.removeNthFromEnd(head, n) << endl;

	head = createList({ 1 }), n = 1;
	cout << sol.removeNthFromEnd(head, n) << endl;

	head = createList({ 1, 2 }), n = 1;
	cout << sol.removeNthFromEnd(head, n) << endl;
}