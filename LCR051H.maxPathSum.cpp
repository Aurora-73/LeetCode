// Created: 2025-12-09
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 路径 被定义为一条从树中任意节点出发，沿父节点-子节点连接，达到任意节点的序列。
同一个节点在一条路径序列中 至多出现一次。该路径 至少包含一个 节点，且不一定经过根节点。
路径和 是路径中各节点值的总和。
给定一个二叉树的根节点 root，返回其 最大路径和，即所有路径上节点值之和的最大值。
示例 1：
	输入：root = {1,2,3}
	输出：6
	解释：最优路径是 2 -> 1 -> 3，路径和为 2 + 1 + 3 = 6
示例 2：
	输入：root = {-10,9,20,null,null,15,7}
	输出：42
	解释：最优路径是 15 -> 20 -> 7，路径和为 15 + 20 + 7 = 42
提示：
	树中节点数目范围是 {1, 3 * 10^4}
	-1000 <= Node.val <= 1000 */

class Solution {
public:
	int maxPathSum(TreeNode *root) {
		int res = numeric_limits<int>::min();
		dfs(root, res);
		return res;
	}

private:
	int dfs(TreeNode *node, int &res) {
		if(!node) {
			return 0;
		}
		int left = max(0, dfs(node->left, res));
		int right = max(0, dfs(node->right, res));
		res = max(left + right + node->val, res);
		// 自己作为根节点的最大路径长度，根节点只有一个，可以连接双侧，可以以根节点作为更新结果的标识
		return max(left, right) + node->val; // 自己作为孩子节点的最大路径长度，孩子只能连接单侧
	}
};
/* 返回以root为根节点，只连接单边的最大路径，计算并更新以root为根节点，可连接双边的路径值
    结果一定是以某个节点为根节点，在这个路径中，仅该节点可以连接自己的两个孩子
    对于每个节点，返回该节点连接自己孩子的最大路径值，也就是自己的父节点作为根节点，且连接自己的情况下的最大路径长度
    对于每个节点都当做根节点计算最大路径长度，并判断是否更新结果 */

int main() {
	Solution sol;
	TreeNode *root;
	root = createTree({ -10, 9, 20, EMPTY_NODE, EMPTY_NODE, 15, 7 });
	cout << sol.maxPathSum(root) << endl;
}