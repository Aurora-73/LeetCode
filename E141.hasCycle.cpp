#include "MyUtils.h"
#include "ListNode.h"

using namespace std;

class Solution {
public:
	bool hasCycle(ListNode *head) {
		if(!head)
			return false;
		ListNode *fast = head->next, *slow = head;
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