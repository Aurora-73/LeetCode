// Created: 2025-05-02
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。
示例 1：
	输入：root = {1,2,3,null,5,null,4}
	输出：{1,3,4}
	解释：
示例 2：
	输入：root = {1,2,3,4,null,null,null,5}
	输出：{1,3,4,5}
	解释：
示例 3：
	输入：root = {1,null,3}
	输出：{1,3}
示例 4：
	输入：root = {}
	输出：{} */

class Solution1 {
public:
	vector<int> rightSideView(TreeNode *root) {
		if(!root) return {}; // 很重要
		vector<int> res;
		queue<TreeNode *> q;
		q.push(root);
		while(!q.empty()) {
			int size = q.size();
			TreeNode *now;
			for(size_t i = 0; i < size; i++) {
				now = q.front();
				q.pop();
				if(now->left) q.push(now->left);
				if(now->right) q.push(now->right);
			}
			res.push_back(now->val);
		}
		return res;
	}
}; // 层次遍历

class Solution {
public:
	vector<int> rightSideView(TreeNode *root) {
		vector<int> res;
		dfs(root, res, 0);
		return res;
	}

private:
	void dfs(TreeNode *root, vector<int> &res, int deepth) {
		if(!root) return;
		if(deepth >= res.size()) {
			res.push_back(root->val);
		}
		dfs(root->right, res, deepth + 1);
		dfs(root->left, res, deepth + 1);
	}
}; // 深度优先遍历

int main() {
	Solution sol;
	TreeNode *root;
	root = createTree({ 1, 2, 3, EMPTY_NODE, 5, EMPTY_NODE, 4 });
	cout << sol.rightSideView(root) << endl; // {1,3,4}

	root = createTree({ 1, 2, 3, 4, EMPTY_NODE, EMPTY_NODE, EMPTY_NODE, 5 });
	cout << sol.rightSideView(root) << endl; // {1,3,4,5}

	root = createTree({ 1, EMPTY_NODE, 3 });
	cout << sol.rightSideView(root) << endl; // {1,3}

	root = createTree({});
	cout << sol.rightSideView(root) << endl; // {}
}