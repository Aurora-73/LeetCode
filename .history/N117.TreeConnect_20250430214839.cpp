// Created: 2025-04-30
#include "MyUtils.h"
#include "MyTreeNode.h"

/*117. 填充每个节点的下一个右侧节点指针 II
给定一个二叉树：
填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL 。
初始状态下，所有 next 指针都被设置为 NULL 。*/
struct Node : TreeNode {
	Node *next;
};

class Solution {
public:
	Node *connect(Node *root) {
		queue<TreeNode *> q;
		Node *prev = nullptr;
		q.push(root);
		int nowlevel = 1, nextlevel = 0, traed = 0;
		while(!q.empty()) {
			TreeNode *now = q.front();
			q.pop();
			if(now->left) {
				q.push(now->left);
			}
			if(now->right) {
				q.push(now->right);
			}
			cout << now->val << " ";
		}
	}
};

int main() {
	Solution sol;
}