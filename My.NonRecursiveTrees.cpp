// Created: 2025-05-01
#include "MyUtils.h"
#include "MyTreeNode.h"

/*二叉树非递归先中后序遍历*/
void PreOrder(TreeNode *root) {
	stack<TreeNode *> s;
	s.push(root);
	while(!s.empty()) {
		TreeNode *now = s.top();
		s.pop();
		// 先右后左，保证左子树先处理
		if(now->right) s.push(now->right);
		if(now->left) s.push(now->left);
		cout << now->val << " ";
	}
}

void InOrder(TreeNode *root) {
	if(!root) return;
	stack<TreeNode *> s;
	TreeNode *now = root;
	while(now || !s.empty()) {
		while(now) {
			s.push(now);
			now = now->left;
		}
		now = s.top();
		s.pop();
		cout << now->val << " ";
		now = now->right;
	}
}

void PostOrder(TreeNode *root) {
	if(!root) return;

	stack<pair<TreeNode *, bool>> s;
	s.push({ root, false });

	while(!s.empty()) {
		auto node = s.top().first;
		auto visited = s.top().second;
		s.pop();

		if(visited) {
			// 第二次遇到，访问
			cout << node->val << " ";
		} else {
			// 第一次遇到，标记为已访问，再把右左子树入栈
			s.push({ node, true }); // 自己标记为“访问过”
			if(node->right) s.push({ node->right, false });
			if(node->left) s.push({ node->left, false });
		}
	}
}

void PostOrder2(TreeNode *root) {
	if(!root) return;

	stack<TreeNode *> s;
	TreeNode *curr = root;
	TreeNode *lastVisited = nullptr;

	while(curr || !s.empty()) {
		// 一路向左
		while(curr) {
			s.push(curr);
			curr = curr->left;
		}

		TreeNode *node = s.top();

		// 如果右子树存在且没访问过，转向右子树
		if(node->right && node->right != lastVisited) {
			curr = node->right;
		} else {
			// 否则访问当前节点，并记录为“最近访问”
			cout << node->val << " ";
			lastVisited = node;
			s.pop();
		}
	}
}

int main() {
	auto tree = createTree({ 1, 2, 3, 4, 5, 6, 7 });
	PreOrder(tree);
	cout << endl;
	InOrder(tree);
	cout << endl;
	PostOrder(tree);
	cout << endl;
}