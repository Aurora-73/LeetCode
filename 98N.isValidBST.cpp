// Created: 2025-05-04
#include "MyTreeNode.h"
#include "MyUtils.hpp"

/*98. 验证二叉搜索树
给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。
有效 二叉搜索树定义如下：
节点的左子树只包含 小于 当前节点的数。
节点的右子树只包含 大于 当前节点的数。
所有左子树和右子树自身必须也是二叉搜索树。*/

class Solution1 {
public:
	bool isValidBST(TreeNode *root) {
		long long prev = numeric_limits<int>::min();
		--prev; // 有可能会存在numeric_limits<int>::min()的节点
		return dfs(root, prev);
	}
	bool dfs(TreeNode *root, long long &prev) {
		if(!root) return true;
		if(!dfs(root->left, prev)) {
			return false;
		}
		if(prev >= root->val) {
			return false;
		}
		prev = root->val;
		if(!dfs(root->right, prev)) {
			return false;
		}
		return true;
	}
};

class Solution2 {
public:
	bool isValidBST(TreeNode *root) {
		int prev = numeric_limits<int>::min();
		return dfs(root, prev);
	}
	bool dfs(TreeNode *root, int &prev) {
		if(!root) return true;
		if(!dfs(root->left, prev)) {
			return false;
		}
		if(begin && prev >= root->val) {
			return false;
		}
		begin = true;
		prev = root->val;
		if(!dfs(root->right, prev)) {
			return false;
		}
		return true;
	}

private:
	bool begin = false;
};

int main() {
	Solution1 sol1;
	Solution2 sol2;
	vector<int> values = { 42, 34, 23, 4, 24, 52, 34, 45, 42, 35, 15, 12, 1, 3 };
	TreeNode *root = createTree(values);
	cout << root << endl;
	bool result1 = sol1.isValidBST(root);
	bool result2 = sol2.isValidBST(root);
	cout << "Solution1 result: " << result1 << endl;
	cout << "Solution2 result: " << result2 << endl;
	deleteTree(root);
	return 0;
}