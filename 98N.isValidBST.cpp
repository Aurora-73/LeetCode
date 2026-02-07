// Created: 2025-05-04
#include "MyTreeNode.h"
#include "MyUtils.hpp"

/* 98. 验证二叉搜索树
给你一个二叉树的根节点 root，判断其是否是一个有效的二叉搜索树。
有效 二叉搜索树定义如下：
	节点的左子树只包含严格小于 当前节点的数。
	节点的右子树只包含 严格大于 当前节点的数。
	所有左子树和右子树自身必须也是二叉搜索树。
示例 1：
	输入：root = {2,1,3}
	输出：true
示例 2：
	输入：root = {5,1,4,null,null,3,6}
	输出：false
	解释：根节点的值是 5，但是右子节点的值是 4。
提示：
	树中节点数目范围在{1, 10^4} 内
	-2^31 <= Node.val <= 231 - 1 */

class Solution1 {
public:
	bool isValidBST(TreeNode *root) {
		long long prev = numeric_limits<long long>::min();
		// 有可能会存在 INT_MIN 的节点
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

class Solution {
public:
	bool isValidBST(TreeNode *root) {
		res = true;
		long long prev = numeric_limits<long long>::min();
		// 用 long long 即可解决左侧值为 INT_MIN 的问题
		inorder(root, prev);
		return res;
	}

private:
	bool res;
	void inorder(TreeNode *root, long long &prev) {
		if(!root || !res) return;
		inorder(root->left, prev);
		if(prev >= root->val) {
			res = false;
			return;
		}
		prev = root->val;
		inorder(root->right, prev);
	}
};

int main() {
	Solution sol;
	TreeNode *root;
	root = createTree({ 5, 1, 4, EMPTY_NODE, EMPTY_NODE, 3, 6 });
	cout << sol.isValidBST(root) << endl;

	root = createTree({ 2, 1, 3 });
	cout << sol.isValidBST(root) << endl;
}