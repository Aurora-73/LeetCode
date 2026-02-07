// Created: 2026-02-06
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给你二叉树的根节点 root，返回它节点值的前序遍历。
示例 1：
	输入：root = {1,EMPTY_NODE,2,3}
	输出：{1,2,3}
	解释：
示例 2：
	输入：root = {1,2,3,4,5,EMPTY_NODE,8,EMPTY_NODE,EMPTY_NODE,6,7,9}
	输出：{1,2,4,5,6,7,3,8,9}
	解释：
示例 3：
	输入：root = {}
	输出：{}
示例 4：
	输入：root = {1}
	输出：{1}
提示：
	树中节点数目在范围 {0, 100} 内
	-100 <= Node.val <= 100
	进阶：递归算法很简单，你可以通过迭代算法完成吗？ */

class Solution1 {
public:
	vector<int> preorderTraversal(TreeNode *root) {
		preorder(root);
		return std::move(res);
	}

private:
	vector<int> res;
	void preorder(TreeNode *root) {
		if(!root) return;
		res.push_back(root->val);
		preorder(root->left);
		preorder(root->right);
	}
};

class Solution {
public:
	vector<int> preorderTraversal(TreeNode *root) {
		vector<int> res;
		stack<TreeNode *> st;
		TreeNode *curr = root;
		while(!st.empty() || curr) {
			while(curr) {
				st.push(curr);
				res.push_back(curr->val);
				// 和非递归中序遍历相比只是入栈时机不同
				curr = curr->left;
			}
			curr = st.top();
			st.pop();
			curr = curr->right;
		}
		return res;
	}
};

int main() {
	Solution sol;
	TreeNode *root;

	root = createTree({ 1, EMPTY_NODE, 2, 3 });
	cout << sol.preorderTraversal(root) << endl;

	root = createTree({ 1, 2, 3, 4, 5, EMPTY_NODE, 8, EMPTY_NODE, EMPTY_NODE, 6, 7, 9 });
	cout << sol.preorderTraversal(root) << endl;

	root = createTree({});
	cout << sol.preorderTraversal(root) << endl;

	root = createTree({ 1 });
	cout << sol.preorderTraversal(root) << endl;
}