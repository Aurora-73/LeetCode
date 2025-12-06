// Created: 2025-12-02
#include "MyListNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定循环单调非递减列表中的一个点，写一个函数向这个列表中插入一个新元素insertVal，使这个列表仍然是循环升序的。
给定的可以是这个列表中任意一个顶点的指针，并不一定是这个列表中最小元素的指针。
如果有多个满足条件的插入位置，可以选择任意一个位置插入新的值，插入后整个列表仍然保持有序。
如果列表为空（给定的节点是 null），需要创建一个循环有序列表并返回这个节点。否则。请返回原先给定的节点。
示例 1：
	输入：head = {3,4,1}, insertVal = 2
	输出：{3,4,1,2}
	解释：在上图中，有一个包含三个元素的循环有序列表，你获得值为 3 的节点的指针，我们需要向表中插入元素 2。
	新插入的节点应该在 1 和 3 之间，插入之后，整个列表如上图所示，最后返回节点 3。
示例 2：
	输入：head = {}, insertVal = 1
	输出：{1}
	解释：列表为空（给定的节点是 null），创建一个循环有序列表并返回这个节点。
示例 3：
	输入：head = {1}, insertVal = 0
	输出：{1,0}
提示：
	0 <= Number of Nodes <= 5 * 10^4
	-10^6 <= Node.val <= 10^6
	-10^6 <=insertVal <= 10^6
注意：本题与主站 708题相同： */

typedef ListNode Node;

class Solution1 {
public:
	Node *insert(Node *head, int insertVal) {
		Node *now = new Node;
		now->val = insertVal;
		if(!head) {
			now->next = now;
			return now;
		}
		Node *maxNode = head->next;
		while(maxNode != head && maxNode->next->val >= maxNode->val) {
			maxNode = maxNode->next;
		}
		Node *minNode = maxNode->next;
		if(insertVal <= minNode->val || insertVal >= maxNode->val) {
			maxNode->next = now;
			now->next = minNode;
			return head;
		}
		auto p = minNode;
		while(p->next->val < insertVal) {
			p = p->next;
		}
		now->next = p->next;
		p->next = now;
		return head;
	}
};

class Solution {
public:
	Node *insert(Node *head, int insertVal) {
		Node *now = new Node;
		now->val = insertVal;
		if(!head) {
			now->next = now;
			return now;
		}
		auto p = head, maxNode = head;
		do {
			if(p->val >= maxNode->val) {
				maxNode = p;
			} // 如果有很多个最大值，要移动到最后一个最大值处
			if(p->val <= insertVal && p->next->val >= insertVal) {
				now->next = p->next;
				p->next = now;
				return head;
			}
			p = p->next;
		} while(p != head);
		now->next = maxNode->next;
		maxNode->next = now;
		return head;
	}
}; // 分为三种情况：1、链表为空  2、待插入值夹在链表的最大最小值之间 3、待插入值大于链表最大值或小于链表最小值
// 第二种情况直接插入在当前值小于等于待插入值，下一个值大于等于待插入值的位置
// 如果不存在第二种情况的位置，则说明是第三种情况，直接插入在最大值之和即可

class Solution2 {
public:
	Node *insert(Node *head, int insertVal) {
		Node *now = new Node(insertVal);
		if(!head) {
			now->next = now;
			return now;
		}

		Node *p = head;
		while(true) {
			// 情形一：正常区间 p->val <= insertVal <= p->next->val
			if(p->val <= insertVal && insertVal <= p->next->val) {
				break;
			}
			// 情形二：转折点：p 为最大，p->next 为最小
			if(p->val > p->next->val) {
				if(insertVal >= p->val || insertVal <= p->next->val) {
					break;
				}
			}
			p = p->next;
			// 遍历一圈后，如果回到 head，说明没有找到合适位置（例如所有元素相同）
			if(p == head) break;
		}

		// 在 p 和 p->next 之间插入
		now->next = p->next;
		p->next = now;
		return head;
	}
};

int main() {
	Solution sol;
}