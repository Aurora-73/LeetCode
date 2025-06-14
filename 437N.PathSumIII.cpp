// Created: 2025-06-14
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 437. 路径总和 III
给定一个二叉树的根节点 root，和一个整数 targetSum，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。
路径 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。
示例 1：
	输入：root = {10,5,-3,3,2,null,11,3,-2,null,1}, targetSum = 8
	输出：3
	解释：和等于 8 的路径有 3 条，如图所示。
示例 2：
	输入：root = {5,4,8,11,null,13,4,7,2,null,null,5,1}, targetSum = 22
	输出：3
提示:
	二叉树的节点个数的范围是 {0,1000}
	-10^9<= Node.val <= 10^9
	-1000<= targetSum<= 1000 */

class Solution {
public:
	int pathSum(TreeNode *root, int targetSum) {
		res = 0;
		prefix = 0;
		prefixCount[0] = 1; // 需要初始化0为1
		dfs(root, targetSum);
		return res;
	}

private:
	unordered_map<long long, unsigned> prefixCount;
	int res;
	long long prefix;
	void dfs(TreeNode *root, int targetSum) {
		if(!root) return;
		prefix += root->val;
		{
			auto it = prefixCount.find(prefix - targetSum);
			if(it != prefixCount.end()) {
				res += it->second;
			}
		}
		auto [it, noFind] = prefixCount.insert({ prefix, 1 });
		if(!noFind) {
			++it->second;
		}
		dfs(root->left, targetSum);
		dfs(root->right, targetSum);
		--it->second;
		prefix -= root->val;
	}
};
// 可以参考 560 题，回朔算法 + 哈希表记录父节点的前缀和，前缀和只差为 tragetSum 即可

int main() {
	Solution sol;
}