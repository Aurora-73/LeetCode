// Created: 2025-04-30
#include "MyUtils.h"
#include "MyTreeNode.h"

/*117. 填充每个节点的下一个右侧节点指针 II
给定一个二叉树：
填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL 。
初始状态下，所有 next 指针都被设置为 NULL 。*/
struct Node {
	int val;
	Node *left;
	Node *right;
	Node *next;
};

class Solution {
public:
	Node *connect(Node *root) {
		if(!root)
			return root;
		queue<Node *> q;
		Node *prev = nullptr;
		q.push(root);
		int nowlevel = 1, nextlevel = 0, count = 0;
		while(!q.empty()) {
			Node *now = q.front();
			q.pop();
			if(now->left) {
				q.push(now->left);
				nextlevel++;
			}
			if(now->right) {
				q.push(now->right);
				nextlevel++;
			}
			if(prev) {
				prev->next = now;
			}
			prev = now;
			count++;
			if(count == nowlevel) {
				nowlevel = nextlevel;
				count = 0;
				prev = nullptr;
			}
		}
		return root;
	}
};

int main() {
	Solution sol;
}