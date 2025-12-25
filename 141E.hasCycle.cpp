#include "MyListNode.h"
#include "MyUtils.hpp"

using namespace std;

class Solution {
public:
	bool hasCycle(ListNode *head) {
		if(!head) return false;
		ListNode *fast = head, *slow = head;
		while(fast && fast->next) {
			fast = fast->next->next;
			slow = slow->next;
			if(fast == slow) {
				return true;
			}
		}
		return false;
	}
};
/* 环形链表（判环／找环入口）
    一定要让 slow = head; fast = head;
    并且用「先移动再判断是否相遇」的方式。
	有环，则让同时移动头结点和重合节点一步，直到两者相遇
找链表中点
    如果偶数长度时想取 右中点，就 fast = head;
    如果想取 左中点，就 fast = head->next; */

int main() {
	ListNode *head = createList({ 1, 3, 4 }), *temp = head;
	Solution sol;
	cout << sol.hasCycle(head) << endl;
	while(temp->next) {
		temp = temp->next;
	}
	temp->next = head;
	cout << sol.hasCycle(head) << endl;
	temp->next = nullptr;
	deleteList(head);
}