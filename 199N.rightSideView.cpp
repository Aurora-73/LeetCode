// Created: 2025-05-02
#include "MyTreeNode.h"
#include "MyUtils.hpp"

/*199. 二叉树的右视图
给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。*/
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
				if(now->left) {
					q.push(now->left);
				}
				if(now->right) {
					q.push(now->right);
				}
			}
			res.push_back(now->val);
		}
		return res;
	}
};

class Solution2 {
public:
	vector<int> rightSideView(TreeNode *root) {
		res.clear();
		dfs(root, 0);
		return res;
	}
	void dfs(TreeNode *root, int deepth) {
		if(!root) return;
		if(deepth == res.size()) {
			res.push_back(root->val);
		}
		dfs(root->right, deepth + 1);
		dfs(root->left, deepth + 1); // 先右后左，选遇到的就是右边的
	}

private:
	vector<int> res;
};

int main() {
	Solution1 sol1;
}