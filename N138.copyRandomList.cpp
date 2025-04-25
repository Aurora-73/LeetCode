// Created: 2025-04-25
#include "MyUtils.h"

/*138. 随机链表的复制
提示
给你一个长度为 n 的链表，每个节点包含一个额外增加的随机指针 random ，该指针可以指向链表中的任何节点或空节点。
构造这个链表的 深拷贝。 深拷贝应该正好由 n 个 全新 节点组成，其中每个新节点的值都设为其对应的原节点的值。
新节点的 next 指针和 random 指针也都应指向复制链表中的新节点，并使原链表和复制链表中的这些指针能够表示相同的链表状态。复制链表中的指针都不应指向原链表中的节点 。
例如，如果原链表中有 X 和 Y 两个节点，其中 X.random --> Y 。那么在复制链表中对应的两个节点 x 和 y ，同样有 x.random --> y 。
返回复制链表的头节点。
用一个由 n 个节点组成的链表来表示输入/输出中的链表。每个节点用一个 [val, random_index] 表示：
val：一个表示 Node.val 的整数。
random_index：随机指针指向的节点索引（范围从 0 到 n-1）；如果不指向任何节点，则为  null 。
你的代码 只 接受原链表的头节点 head 作为传入参数。*/

class Node {
public:
	int val;
	Node *next;
	Node *random;
	Node(int _val) {
		val = _val;
		next = NULL;
		random = NULL;
	}
};

class Solution0 {
public:
	Node *copyRandomList(Node *head) {
		if(!head) {
			return nullptr;
		}
		unordered_map<Node *, Node *> old2new;
		Node *oldIter = head->next, *res = new Node(head->val), *newIter = res;
		old2new[head] = res;
		while(oldIter) {
			newIter->next = new Node(oldIter->val);
			old2new[oldIter] = newIter->next;
			oldIter = oldIter->next;
			newIter = newIter->next;
		}
		oldIter = head;
		newIter = res;
		while(oldIter) {
			newIter->random = old2new[oldIter->random];
			oldIter = oldIter->next;
			newIter = newIter->next;
		}
		return res;
	}
};

class Solution1 {
public:
	Node *copyRandomList(Node *head) {
		unordered_map<Node *, Node *> old2new {}; // 默认为空指针
		for(Node *temp = head; temp; temp = temp->next) {
			old2new[temp] = new Node(temp->val);
		}
		for(auto pair : old2new) {
			if(pair.first) { // 查找会产生空指针，也可能被遍历到
				pair.second->next = old2new[pair.first->next];
				pair.second->random = old2new[pair.first->random];
			}
		}
		return old2new[head];
	}
}; // 性能不如第一个，连接next也要查找

class Solution2 {
public:
	Node *copyRandomList(Node *head) {
		if(!head) {
			return head;
		}
		for(Node *node = head; node; node = node->next->next) {
			Node *newNode = new Node(node->val);
			newNode->next = node->next;
			node->next = newNode;
		}
		for(Node *node = head; node; node = node->next->next) {
			if(node->random) {
				node->next->random = node->random->next;
			} // 默认为空
		}
		Node *newHead = head->next;
		for(Node *node = head; node; node = node->next) {
			Node *temp = node->next;
			node->next = temp->next;
			if(temp->next) {
				temp->next = temp->next->next;
			} // 默认为空
		}
		return newHead;
	}
};
// 在原来的每个节点后面拷贝一个新节点，则奇数节点为旧节点，偶数节点为新节点
// 对于每个旧节点，它的后一个节点就是它对应的新节点，这样就可以构造random，但是需要单独处理空节点
// 最后将新旧节点分开即可

Node *createTestList() {
	vector<Node *> nodes;
	for(int val : { 7, 13, 11, 10, 1 })
		nodes.push_back(new Node(val));

	nodes[0]->next = nodes[1];
	nodes[1]->next = nodes[2];
	nodes[2]->next = nodes[3];
	nodes[3]->next = nodes[4];

	nodes[0]->random = nullptr;
	nodes[1]->random = nodes[0];
	nodes[2]->random = nodes[4];
	nodes[3]->random = nodes[2];
	nodes[4]->random = nodes[0];

	return nodes[0]; // 返回头节点
}

void printList(Node *head) {
	Node *curr = head;
	while(curr) {
		cout << curr->val << " (";
		if(curr->random)
			cout << curr->random->val;
		else
			cout << "null";
		cout << ") -> ";
		curr = curr->next;
	}
	cout << "null\n";
}

int main() {
	Solution0 sol0;
	Solution1 sol1;
	Solution2 sol2;

	Node *original = createTestList();
	cout << "Original:\n";
	printList(original);

	cout << "\nSolution0:\n";
	Node *res0 = sol0.copyRandomList(original);
	printList(res0);

	cout << "\nSolution1:\n";
	Node *res1 = sol1.copyRandomList(original);
	printList(res1);

	cout << "\nSolution2:\n";
	Node *res2 = sol2.copyRandomList(original);
	printList(res2);

	return 0;
}