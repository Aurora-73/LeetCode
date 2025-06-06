// Created: 2025-04-30
#include "MyTreeNode.h"
#include "MyUtils.hpp"

/* 129. 求根节点到叶节点数字之和
给你一个二叉树的根节点 root ，树中每个节点都存放有一个 0 到 9 之间的数字。
每条从根节点到叶节点的路径都代表一个数字：
例如，从根节点到叶节点的路径 1 -> 2 -> 3 表示数字 123 。
计算从根节点到叶节点生成的 所有数字之和 。
叶节点 是指没有子节点的节点。*/

class Solution {
public:
	int sumNumbers(TreeNode *root) {
		sum = 0;
		LeafSum(root, 0);
		return sum;
	}
	void LeafSum(TreeNode *root, int pre) {
		if(!root) return;
		pre *= 10;
		pre += root->val;
		if(!root->left && !root->right) {
			sum += pre;
			return;
		}
		LeafSum(root->left, pre);
		LeafSum(root->right, pre);
	}

private:
	int sum = 0;
};

int main() {
	Solution sol;
}