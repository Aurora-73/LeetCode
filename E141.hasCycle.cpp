#include <iostream>
#include <vector>
#include <unordered_map>
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