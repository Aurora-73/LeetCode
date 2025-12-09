// Created: 2025-12-08
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个二叉树的 根节点 root，请找出该二叉树的最底层最左边节点的值。
假设二叉树中至少有一个节点。
示例 1：
	输入: root = {2,1,3}
	输出: 1
示例 2：
	输入: {1,2,3,4,null,5,6,null,null,7}
	输出: 7
提示：
	二叉树的节点个数的范围是 {1,10^4}*/

class Solution1 {
public:
	int findBottomLeftValue(TreeNode *root) {
		int res;
		queue<TreeNode *> que;
		que.push(root);
		while(!que.empty()) {
			int n = que.size();
			res = que.front()->val;
			for(int i = 0; i < n; ++i) {
				auto p = que.front();
				que.pop();
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

class Solution2 {
public:
	int findBottomLeftValue(TreeNode *root) {
		max_deepth = -1;
		DFS(root, 0);
		return res;
	}

private:
	void DFS(TreeNode *root, int deepth) {
		if(!root) {
			return;
		}
		if(deepth > max_deepth) {
			max_deepth = deepth;
			res = root->val;
		}

		DFS(root->left, deepth + 1);
		DFS(root->right, deepth + 1);
	}
	int max_deepth, res;
}; // DFS

class Solution {
public:
	int findBottomLeftValue(TreeNode *root) {
		int ret;
		queue<TreeNode *> q;
		q.push(root);
		while(!q.empty()) {
			auto p = q.front();
			q.pop();
			if(p->right) {
				q.push(p->right);
			}
			if(p->left) {
				q.push(p->left);
			}
			ret = p->val;
		}
		return ret;
	}
}; // BFS 先右后左

int main() {
	Solution sol;
	TreeNode *root;
	cout << sol.findBottomLeftValue(root) << endl;
}