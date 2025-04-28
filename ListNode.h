#ifndef MY_ListNode
#define MY_ListNode

struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) { }
	ListNode(int x) : val(x), next(nullptr) { }
	ListNode(int x, ListNode *next) : val(x), next(next) { }
};

/**
 * 创建值为1到n的链表
 * @param n 链表长度
 * @return 链表头节点
 */
ListNode *createList(int n) {
	if(n <= 0)
		return nullptr;

	ListNode *head = new ListNode(1);
	ListNode *current = head;

	for(int i = 2; i <= n; i++) {
		current->next = new ListNode(i);
		current = current->next;
	}

	return head;
}

/**
 * 根据整数数组创建链表
 * @param values 整数数组
 * @return 链表头节点
 */
ListNode *createList(const std::vector<int> &values) {
	if(values.empty())
		return nullptr;

	ListNode *head = new ListNode(values[0]);
	ListNode *current = head;

	for(size_t i = 1; i < values.size(); i++) {
		current->next = new ListNode(values[i]);
		current = current->next;
	}

	return head;
}

/**
* 输出链表
* @param 链表头节点
*/
ostream &operator<<(ostream &os, ListNode *head) {
	os << "{ ";
	while(head) {
		os << head->val;
		head = head->next;
		if(head) {
			os << " -> ";
		}
	}
	return os << " }";
}

/**
 * 释放链表内存
 * @param head 链表头节点
 */
void deleteList(ListNode *head) {
	while(head) {
		ListNode *temp = head;
		head = head->next;
		delete temp;
	}
}

#endif // MY_ListNode