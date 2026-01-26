// Created: 2025-06-11
#include "MyDateGen.h"
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 94. 二叉树的中序遍历
给定一个二叉树的根节点 root，返回 它的 中序遍历。
示例 1：
	输入：root = {1,null,2,3}
	输出：{1,3,2}
示例 2：
	输入：root = {}
	输出：{}
示例 3：
	输入：root = {1}
	输出：{1}
提示：
	树中节点数目在范围 {0, 100} 内
	-100 <= Node.val <= 100
	进阶:递归算法很简单，你可以通过迭代算法完成吗？ */

class Solution1 {
public:
	vector<int> inorderTraversal(TreeNode *root) {
		vector<int> res;
		inorder(root, res);
		return res;
	}

private:
	void inorder(TreeNode *root, vector<int> &res) {
		if(!root) return;
		inorder(root->left, res);
		res.push_back(root->val);
		inorder(root->right, res);
	}
};

class Solution {
public:
	vector<int> inorderTraversal(TreeNode *root) {
		vector<int> res;
		stack<TreeNode *> st;
		TreeNode *now = root;
		while(now || st.size()) {
			while(now) {
				st.push(now);
				now = now->left;
			}
			now = st.top();
			st.pop();
			res.push_back(now->val);
			now = now->right;
		}
		return res;
	}
}; // 首先找到当前节点的最左侧节点，将过程中遍历到的节点全部入栈
// 然后遍历栈顶节点，由于该节点一定没有左子树，转到该节点的右孩子处

int main() {
	Solution sol;
	TreeNode *root;
	root = createTree({ 1, EMPTY_NODE, 2, 3 });
	cout << sol.inorderTraversal(root) << endl;

	root = createTree({});
	cout << sol.inorderTraversal(root) << endl;

	root = createTree({ 1 });
	cout << sol.inorderTraversal(root) << endl;
}
