// Created: 2025-04-30
#include "MyUtils.h"
#include "MyTreeNode.h"

/*  */

void levelTraversal(TreeNode *root) {
	queue<TreeNode *> q;
	q.push(root);
	while(!q.empty()) {
		TreeNode *now = q.front();
		q.pop();
		if(now->left) {
			q.push(now->left);
		}
		if(now->right) {
			q.push(now->right);
		}
		cout << now->val;
	}
}

int main() {
	levelTraversal(createTree({ 1, 2, 3, 4, 5, -1, 7 }));
}