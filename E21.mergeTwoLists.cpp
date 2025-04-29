#include "MyUtils.h"
#include "MyListNode.h"

using namespace std;

class Solution {
public:
	ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
		ListNode *head = new ListNode(), *tail = head;
		while(list1 && list2) {
			if(list1->val <= list2->val) {
				tail->next = list1;
				list1 = list1->next;
				tail = tail->next;
			} else {
				tail->next = list2;
				list2 = list2->next;
				tail = tail->next;
			}
		}
		tail->next = list1 ? list1 : list2;
		tail = head;
		head = head->next;
		delete tail;
		return head;
	}
};

int main() {
	ListNode *list1 = createList({1, 3, 4});
	ListNode *list2 = createList({2, 5, 9});
	Solution sol;
	ListNode *res = sol.mergeTwoLists(list1, list2);
	cout << res << endl;
	deleteList(res);
}