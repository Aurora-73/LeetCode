#include "MyTreeNode.h"
#include "MyUtils.hpp"

/* 给你一个二叉树的根节点 root， 检查它是否轴对称。
示例 1：
	输入：root = {1,2,2,3,4,4,3}
	输出：true
示例 2：
	输入：root = {1,2,2,null,3,null,3}
	输出：false
提示：
	树中节点数目在范围 {1, 1000} 内
	-100 <= Node.val <= 100
	进阶：你可以运用递归和迭代两种方法解决这个问题吗？ */

class Solution1 {
public:
	bool isSymmetric(TreeNode *root) {
		res = true;
		if(root) isEqual(root->left, root->right);
		return res;
	}

private:
	bool res;
	void isEqual(TreeNode *a, TreeNode *b) {
		if(!res) return;
		if(!a && !b) return;
		if(!a || !b || a->val != b->val) {
			res = 0;
			return;
		}
		isEqual(a->left, b->right);
		isEqual(a->right, b->left);
	}
}; // 递归写法

class Solution {
public:
	bool isSymmetric(TreeNode *root) {
		if(!root) return true;

		queue<TreeNode *> q;
		q.push(root->left);
		q.push(root->right);

		while(!q.empty()) {
			TreeNode *left = q.front();
			q.pop();
			TreeNode *right = q.front();
			q.pop();

			if(!left && !right) continue;
			if(!left || !right) return false;
			if(left->val != right->val) return false;

			// 按“镜像”顺序入队
			q.push(left->left);
			q.push(right->right);
			q.push(left->right);
			q.push(right->left);
		}

		return true;
	}
}; // 迭代写法

int main() {
	Solution sol;
	TreeNode *root;
	root = createTree({ 1, 2, 2, 3, 4, 4, 3 });
	cout << sol.isSymmetric(root) << endl;

	root = createTree({ 1, 2, 2, EMPTY_NODE, 3, EMPTY_NODE, 3 });
	cout << sol.isSymmetric(root) << endl;
}