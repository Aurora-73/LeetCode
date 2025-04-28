#include "MyUtils.h"
#include "ListNode.h"

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