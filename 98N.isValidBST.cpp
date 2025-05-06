// Created: 2025-05-04
#include "MyUtils.h"
#include "MyTreeNode.h"

/*98. 验证二叉搜索树
给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。
有效 二叉搜索树定义如下：
节点的左子树只包含 小于 当前节点的数。
节点的右子树只包含 大于 当前节点的数。
所有左子树和右子树自身必须也是二叉搜索树。*/

class Solution1 {
public:
	bool isValidBST(TreeNode *root) {
		long long prev = INT_MIN;
		--prev; // 有可能会存在INT_MIN的节点
		return dfs(root, prev);
	}
	bool dfs(TreeNode *root, long long &prev) {
		if(!root)
			return true;
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
		int prev = INT_MIN;
		return dfs(root, prev);
	}
	bool dfs(TreeNode *root, int &prev) {
		if(!root)
			return true;
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
}