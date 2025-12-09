// Created: 2025-12-08
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。
示例 1：
	输入:{1,2,3,null,5,null,4}
	输出:{1,3,4}
示例 2：
	输入:{1,null,3}
	输出:{1,3}
示例 3：
	输入:{}
	输出:{}
提示：
	二叉树的节点个数的范围是 {0,100}
	-100<= Node.val <= 100
注意：本题与主站 199题相同： */

class Solution1 {
public:
	vector<int> rightSideView(TreeNode *root) {
		if(!root) return {};
		vector<int> res;
		queue<TreeNode *> que;
		que.push(root);
		while(!que.empty()) {
			int n = que.size();
			for(int i = 0; i < n; ++i) {
				auto p = que.front();
				que.pop();
				if(i == n - 1) {
					res.push_back(p->val);
				}
				if(p->left) {
					que.push(p->left);
				}
				if(p->right) {
					que.push(p->right);
				}
			}
		}
		return res;
	}
}; // BFS

class Solution {
public:
	vector<int> rightSideView(TreeNode *root) {
		vector<int> res;
		DFS(root, 0, res);
		return res;
	}

private:
	void DFS(TreeNode *root, int deepth, vector<int> &res) {
		if(!root) {
			return;
		}
		if(deepth >= res.size()) {
			res.push_back(root->val);
		}

		DFS(root->right, deepth + 1, res);
		DFS(root->left, deepth + 1, res);
	}
}; // DFS

int main() { }