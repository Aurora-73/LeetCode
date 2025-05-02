// Created: 2025-05-02
#include "MyUtils.h"
#include "MyTreeNode.h"

/*124. 二叉树中的最大路径和
二叉树中的 路径 被定义为一条节点序列，序列中每对相邻节点之间都存在一条边。
同一个节点在一条路径序列中 至多出现一次 。该路径 至少包含一个 节点，且不一定经过根节点。
路径和 是路径中各节点值的总和。
给你一个二叉树的根节点 root ，返回其 最大路径和 。*/

class Solution {
public:
	int maxPathSum(TreeNode *root) {
		maxPath = INT_MIN;
		dfs(root);
		return maxPath;
	}
	int dfs(TreeNode *root) {
		if(!root)
			return 0;
		int l = max(dfs(root->left), 0);
		int r = max(dfs(root->right), 0);
		int newLink = root->val + r + l;
		maxPath = max(newLink, maxPath); // 不要当前节点的父节点，自立为王
		// 只能参与一个路径，当递归到某个节点的时候
		// 它和它的父节点的链接和它和它左右节点的链接只能保留一个
		return root->val + max(r, l); // 要当前节点的父节点，只能保留一个子树
		// 留一个最大的，另一边给父节点
	}
	int maxPath = INT_MIN;
};
// 二叉树中每个节点最多有三个连线
// 但是在路径中一个节点最多有两个连线

int main() {
	Solution sol;
}