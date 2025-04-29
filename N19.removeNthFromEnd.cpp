// Created: 2025-04-25
#include "MyUtils.h"
#include "MyListNode.h"

/*  19. 删除链表的倒数第 N 个结点
给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。*/

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

class Solution2 {
public:
	ListNode *removeNthFromEnd(ListNode *head, int n) {
		ListNode *fast = head, *slow = nullptr;
		for(int i = 0; i < n; ++i) {
			fast = fast->next;
		}
		if(!fast) {
			ListNode *temp = head;
			head = head->next;
			delete temp;
			return head;
		}
		slow = head;
		while(fast->next) {
			slow = slow->next;
			fast = fast->next;
		}
		ListNode *temp = slow->next;
		slow->next = slow->next->next;
		delete temp;
		return head;
	}
};
// 没有头结点不能让 fast 先走 n+1 步，因为删除最后一个节点时根本就没有 n+1 步可以走
// 如果走了 n 步 fast 已经为空了，则说明要删除的就是第一个节点
// 否则开始同步移动 fast 和 slow ，由于 slow 要指向前一个节点，因此当 fast->next 为空时就已经可以停止移动了

int main() {
	ListNode *head = createList(6);
	cout << head << endl;
	Solution1 sol1;
	sol1.removeNthFromEnd(head, 2);
	cout << head << endl;
	Solution2 sol2;
	sol2.removeNthFromEnd(head, 2);
	cout << head << endl;
	deleteList(head);
}