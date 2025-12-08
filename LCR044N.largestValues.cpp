// Created: 2025-12-08
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一棵二叉树的根节点root，请找出该二叉树中每一层的最大值。
示例 1： 输入 : root
	                    = { 1, 3, 2, 5, 3, null, 9 } 输出 : { 1, 3, 9 } 解释 : 1 / 3 2 / \ 5 3 9
示例 2： 输入
	    : root = { 1, 2, 3 } 输出 : { 1, 3 } 解释 : 1
	                                / 2 3
示例 3： 输入
	    : root = {1} 输出 : {1}
示例 4： 输入 : root = { 1, null, 2 } 输出 : { 1, 2 }

示例 5： 输入: root
	      = {} 输出 : {}
提示： 二叉树的节点个数的范围是{0, 10 ^ 4} */

class Solution {
public:
	vector<int> largestValues(TreeNode *root) {
		if(!root) return {};
		vector<int> res;
		queue<TreeNode *> que;
		que.push(root);
		while(!que.empty()) {
			int size = que.size(), max_val = INT_MIN;
			for(int i = 0; i < size; ++i) {
				auto q = que.front();
				que.pop();
				max_val = max(max_val, q->val);
				if(q->left) {
					que.push(q->left);
				}
				if(q->right) {
					que.push(q->right);
				}
			}
			res.push_back(max_val);
		}
		return res;
	}
}; // 广度优先

class Solution1 {
public:
	vector<int> largestValues(TreeNode *root) {
		vector<int> res;
		DFS(root, 0, res);
		return res;
	}

private:
	void DFS(TreeNode *root, int height, vector<int> &res) {
		if(!root) return;
		if(res.size() <= height) {
			res.push_back(root->val);
		} else {
			res[height] = max(res[height], root->val);
		}
		DFS(root->left, height + 1, res);
		DFS(root->right, height + 1, res);
	}
}; // 深度优先

int main() {
	Solution sol;
	TreeNode *root;
	cout << sol.largestValues(root) << endl;
}