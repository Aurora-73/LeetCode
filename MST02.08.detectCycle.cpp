// Created: 2025-12-24
#include "MyListNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 面试题 02.08. 环路检测
给定一个链表，如果它是有环链表，实现一个算法返回环路的开头节点。若环不存在，请返回 null。
如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。 为了表示给定链表中的环，我们使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。
 如果 pos 是 -1，则在该链表中没有环。注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。
示例 1：
	输入：head = {3,2,0,-4}, pos = 1
	输出：tail connects to node index 1
	解释：链表中有一个环，其尾部连接到第二个节点。
示例 2：
	输入：head = {1,2}, pos = 0
	输出：tail connects to node index 0
	解释：链表中有一个环，其尾部连接到第一个节点。
示例 3：
	输入：head = {1}, pos = -1
	输出：no cycle
	解释：链表中没有环。 */

class Solution {
public:
	ListNode *detectCycle(ListNode *head) {
		ListNode *fast = head, *slow = head;
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
}; // 先用快慢指针确定有没有环，注意这个时候需要先走后判断相与，均从head开始走。有环，则让同时移动头结点和重合节点一步，直到两者相遇
/* 环形链表（判环／找环入口）
    一定要让 slow = head; fast = head;
    并且用「先移动再判断是否相遇」的方式。
	有环，则让同时移动头结点和重合节点一步，直到两者相遇，相遇点即为交叉点
找链表中点
    如果偶数长度时想取 右中点，就 fast = head;
    如果想取 左中点，就 fast = head->next; */
/* 更进一步，如果需要断开环，则用另外一个指针p在中行走，直到 p->next 是环的入口，让 p->next = nullptr 即可*/

int main() {
	Solution sol;
	ListNode *head;
	cout << sol.detectCycle(head) << endl;
}