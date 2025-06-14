// Created: 2025-06-14
#include "MyDateGen.h"
#include "MyListNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 142. 环形链表 II
给定一个链表的头节点 head，返回链表开始入环的第一个节点。
如果链表无环，则返回null。
如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。
如果 pos 是 -1，则在该链表中没有环。注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。
不允许修改 链表。
示例 1：
	输入：head = {3,2,0,-4}, pos = 1
	输出：返回索引为 1 的链表节点
	解释：链表中有一个环，其尾部连接到第二个节点。
示例2：
	输入：head = {1,2}, pos = 0
	输出：返回索引为 0 的链表节点
	解释：链表中有一个环，其尾部连接到第一个节点。
示例 3：
	输入：head = {1}, pos = -1
	输出：返回 null
	解释：链表中没有环。
提示：
	链表中节点的数目范围在范围 {0, 10^4} 内
	-10^5 <= Node.val <= 10^5
	pos 的值为 -1 或者链表中的一个有效索引
	进阶：你是否可以使用 O(1) 空间解决此题？ */

class Solution {
public:
	ListNode *detectCycle(ListNode *head) {
		if(!head || !head->next) {
			return nullptr;
		}
		ListNode *slow = head, *fast = head;
		while(fast && fast->next) {
			fast = fast->next->next;
			slow = slow->next;
			if(fast == slow) break;
		}
		if(!fast || !fast->next) {
			return nullptr;
		}
		fast = head;
		while(fast != slow) {
			fast = fast->next;
			slow = slow->next;
		}
		return fast;
	}
};
// 先用快慢指针确定有没有环，有环，则让同时移动头结点和重合节点一步，直到两者相遇
/* 环形链表（判环／找环入口）
    一定要让 slow = head; fast = head;
    并且用「先移动再判断是否相遇」的方式。这样逻辑最简洁、最不容易出错。
找链表中点
    如果偶数长度时想取 右中点，就 fast = head;。
    如果想取 左中点，就 fast = head->next; */

int main() {
	Solution sol;
}