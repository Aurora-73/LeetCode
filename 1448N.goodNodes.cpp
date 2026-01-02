// Created: 2025-07-05
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 1448. 统计二叉树中好节点的数目
给你一棵根为root的二叉树，请你返回二叉树中好节点的数目。
「好节点」X 定义为：从根到该节点 X 所经过的节点中，没有任何节点的值大于 X 的值。
示例 1：
	输入：root = {3,1,4,3,EMPTY_NODE,1,5}
	输出：4
	解释：图中蓝色节点为好节点。
	根节点 (3) 永远是个好节点。
	节点 4 -> (3,4) 是路径中的最大值。
	节点 5 -> (3,4,5) 是路径中的最大值。
	节点 3 -> (3,1,3) 是路径中的最大值。
示例 2：
	输入：root = {3,3,EMPTY_NODE,4,2}
	输出：3
	解释：节点 2 -> (3, 3, 2) 不是好节点，因为 "3" 比它大。
示例 3：
	输入：root = {1}
	输出：1
	解释：根节点是好节点。
提示：
	二叉树中节点数目范围是{1, 10^5}。
	每个节点权值的范围是{-10^4, 10^4}。 */

class Solution1 {
public:
	int goodNodes(TreeNode *root) {
		res = 0;
		dfs(root, numeric_limits<int>::min());
		return res;
	}

private:
	int res;
	void dfs(TreeNode *root, int max_val) {
		if(!root) return;
		if(root->val >= max_val) {
			max_val = root->val;
			++res;
		}
		dfs(root->left, max_val);
		dfs(root->right, max_val);
	}
};

class Solution {
public:
	int goodNodes(TreeNode *root, int mx = numeric_limits<int>::min()) {
		if(root == nullptr) return 0;
		int res = 0;
		if(root->val >= mx) {
			++res;
			mx = root->val;
		}
		res += goodNodes(root->left, mx);
		res += goodNodes(root->right, mx);
		return res;
	} // 参数设置默认值，直接遍历
};

int main() {
	Solution sol;
	TreeNode *root;
	root = createTree({ 3, 1, 4, 3, EMPTY_NODE, 1, 5 });
	cout << sol.goodNodes(root) << endl; // 4
	root = createTree({ 3, 3, EMPTY_NODE, 4, 2 });
	cout << sol.goodNodes(root) << endl; // 3
	root = createTree({ 1 });
	cout << sol.goodNodes(root) << endl; // 1
}