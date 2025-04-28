#ifndef MY_ListNode
#define MY_ListNode

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) { }
	ListNode(int x) : val(x), next(nullptr) { }
	ListNode(int x, ListNode *next) : val(x), next(next) { }
};

#endif // MY_ListNode