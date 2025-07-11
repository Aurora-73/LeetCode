// Created: 2025-06-28
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 153. 二叉树中和为目标值的路径
给你二叉树的根节点 root 和一个整数目标和 targetSum，找出所有 从根节点到叶子节点 路径总和等于给定目标和的路径。
叶子节点 是指没有子节点的节点。
示例 1：
	输入：root = {5,4,8,11,null,13,4,7,2,null,null,5,1}, targetSum = 22
	输出：{{5,4,11,2},{5,8,4,5}}
示例 2：
	输入：root = {1,2,3}, targetSum = 5
	输出：{}
示例 3：
	输入：root = {1,2}, targetSum = 0
	输出：{}
提示：
	树中节点总数在范围 {0, 5000} 内
	-1000 <= Node.val <= 1000
	-1000 <= targetSum <= 1000 */

class Solution {
public:
	vector<vector<int>> pathTarget(TreeNode *root, int target) {
		res.clear(), now.clear();
		dfs(root, target);
		return res;
	}

private:
	vector<int> now;
	vector<vector<int>> res;
	void dfs(TreeNode *root, int target) {
		if(root == nullptr) return;
		target -= root->val;
		now.push_back(root->val);
		if(!root->left && !root->right && target == 0) {
			res.push_back(now); // 根 到 叶子
		} else {
			dfs(root->left, target);
			dfs(root->right, target);
		}
		target += root->val;
		now.pop_back();
	}
};

int main() {
	Solution sol;
	TreeNode *root;
	int target;
	root = createTree({ 5, 4, 8, 11, EMPTY_NODE, 13, 4, 7, 2, EMPTY_NODE, EMPTY_NODE, 5, 1 });
	target = 22;
	cout << sol.pathTarget(root, target) << endl; // {{5,4,11,2},{5,8,4,5}}
	root = createTree({ 1, 2, 3 });
	target = 5;
	cout << sol.pathTarget(root, target) << endl; // {}
	root = createTree({ 1, 2 });
	target = 0;
	cout << sol.pathTarget(root, target) << endl; // {}
	root = createTree({ 1, 2 });
	target = 1;
	cout << sol.pathTarget(root, target) << endl; // {}
}