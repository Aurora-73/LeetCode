// Created: 2025-12-02
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

class Node {
public:
	int val;
	Node *prev;
	Node *next;
	Node *child;
};

/* 多级双向链表中，除了指向下一个节点和前一个节点指针之外，它还有一个子链表指针，可能指向单独的双向链表。
这些子列表也可能会有一个或多个自己的子项，依此类推，生成多级数据结构，如下面的
示例所示。
给定位于列表第一级的头节点，请扁平化列表，即将这样的多级双向链表展平成普通的双向链表，使所有结点出现在单级双链表中。
示例 1：
	输入：head = {1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12}
	输出：{1,2,3,7,8,11,12,9,10,4,5,6}
	解释：
	输入的多级列表如下图所示：
	扁平化后的链表如下图：
示例 2：
	输入：head = {1,2,null,3}
	输出：{1,3,2}
	解释：
	输入的多级列表如下图所示：
	  1---2---NULL
	  |
	  3---NULL
示例 3：
	输入：head = {}
	输出：{}
	如何表示测试用例中的多级链表？
	以 
	示例 1 为例：
	 1---2---3---4---5---6--NULL
	         |
	         7---8---9---10--NULL
	             |
	             11--12--NULL
	序列化其中的每一级之后：
	{1,2,3,4,5,6,null}
	{7,8,9,10,null}
	{11,12,null}
	为了将每一级都序列化到一起，我们需要每一级中添加值为 null 的元素，以表示没有节点连接到上一级的上级节点。
	{1,2,3,4,5,6,null}
	{null,null,7,8,9,10,null}
	{null,11,12,null}
	合并所有序列化结果，并去除末尾的 null。
	{1,2,3,4,5,6,null,null,null,7,8,9,10,null,null,11,12}
提示：
	节点数目不超过 1000
	1 <= Node.val <= 10^5
注意：本题与主站 430题相同： */

class Solution1 {
public:
	Node *flatten(Node *head) {
		for(auto p = head; p != nullptr; p = p->next) {
			if(p->child) {
				auto next = p->next;
				p->next = flatten(p->child);
				while(p->next != nullptr) {
					p = p->next;
				}
				p->next = next;
			}
		}
		for(auto p = head; p && p->next; p = p->next) {
			p->next->prev = p;
			p->child = nullptr;
		}
		return head;
	}
};
// 即将child移动为next，优先级高于next，递归来写

class Solution {
public:
	Node *flatten(Node *head) {
		RetEnd(head);
		return head;
	}

private:
	// 返回扁平化后链表的尾节点（若 head 为空，返回 nullptr）
	Node *RetEnd(Node *head) {
		if(!head) return nullptr;
		Node *p = head;
		while(p) {
			if(p->child) {
				Node *next = p->next;
				Node *childHead = p->child;

				// 先递归扁平化子链表，得到尾节点
				Node *childTail = RetEnd(childHead);

				// 现在一次性连接 childHead/tail
				p->next = childHead;
				childHead->prev = p;
				p->child = nullptr;

				childTail->next = next;
				if(next) next->prev = childTail;

				// 将 p 移到 childTail（接下来的循环从 childTail->next 开始）
				p = childTail;
			}

			if(!p->next) return p;
			p = p->next;
		}
		return nullptr;
	}
};

int main() {
	Solution sol;
}