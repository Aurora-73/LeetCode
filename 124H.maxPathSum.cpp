// Created: 2025-05-02
#include "MyTreeNode.h"
#include "MyUtils.hpp"

/* 二叉树中的 路径 被定义为一条节点序列，序列中每对相邻节点之间都存在一条边。
同一个节点在一条路径序列中 至多出现一次。该路径 至少包含一个 节点，且不一定经过根节点。
路径和 是路径中各节点值的总和。
给你一个二叉树的根节点 root，返回其 最大路径和。
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

class Solution1 {
public:
	int maxPathSum(TreeNode *root) {
		maxPath = numeric_limits<int>::min();
		dfs(root);
		return maxPath;
	}

private:
	int maxPath;
	int dfs(TreeNode *root) {
		if(!root) return 0;
		int l = max(dfs(root->left), 0);
		int r = max(dfs(root->right), 0);
		int newLink = root->val + r + l;
		maxPath = max(newLink, maxPath); // 不要当前节点的父节点，自立为王
		// 只能参与一个路径，当递归到某个节点的时候
		// 它和它的父节点的链接和它和它左右节点的链接只能保留一个
		return root->val + max(r, l); // 要当前节点的父节点，只能保留一个子树
		                              // 留一个最大的，另一边给父节点
	}
};
// 二叉树中每个节点最多有三个连线
// 但是在路径中一个节点最多有两个连线

class Solution {
public:
	int maxPathSum(TreeNode *root) {
		vec_num = INT_MIN;
		dfs(root);
		return vec_num;
	}

private:
	int vec_num;
	int dfs(TreeNode *root) {
		if(!root) return 0;
		int lg = max(0, dfs(root->left));
		int rg = max(0, dfs(root->right));
		vec_num = max(vec_num, root->val + lg + rg);
		return max(lg, rg) + root->val;
	}
}; // 返回root作为单侧根的最大贡献，更新以root为根的最优路径
/*  返回以root为根节点，只连接单边的最大路径，计算并更新以root为根节点，可连接双边的路径值
	结果一定是以某个节点为根节点，在这个路径中，仅该节点可以连接自己的两个孩子
	对于每个节点，返回该节点连接自己孩子的最大路径值，也就是自己的父节点作为根节点，且连接自己的情况下的最大路径长度
	对于每个节点都当做根节点计算最大路径长度，并判断是否更新结果 */

int main() {
	Solution sol;
	TreeNode *root;
	root = createTree({ 1, 2, 3 });
	cout << sol.maxPathSum(root) << endl;

	root = createTree({ -10, 9, 20, EMPTY_NODE, EMPTY_NODE, 15, 7 });
	cout << sol.maxPathSum(root) << endl;
}