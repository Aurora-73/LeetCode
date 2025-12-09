// Created: 2025-12-08
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个二叉树的根节点 root，和一个整数 targetSum，求该二叉树里节点值之和等于 targetSum 的 路径 的数目。
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

class Solution1 {
public:
	int pathSum(TreeNode *root, int targetSum) {
		if(!root) return 0;
		int res = countFrom(root, targetSum);
		res += pathSum(root->left, targetSum);
		res += pathSum(root->right, targetSum);
		return res;
	}

private:
	int countFrom(TreeNode *node, int remain) {
		if(!node) return 0;
		int cnt = (node->val == remain) ? 1 : 0;
		cnt += countFrom(node->left, remain - node->val);
		cnt += countFrom(node->right, remain - node->val);
		return cnt;
	}
}; // 很难写出来

class Solution {
public:
	int pathSum(TreeNode *root, int targetSum) {
		res = 0, target = targetSum;
		cnt.clear();
		cnt[0] = 1;
		DFS(root, 0);
		return res;
	}

private:
	void DFS(TreeNode *root, long curr_sum) {
		if(!root) return;
		curr_sum += root->val;
		auto it = cnt.find(curr_sum - target);
		if(it != cnt.end()) {
			res += it->second;
		}
		++cnt[curr_sum];
		DFS(root->left, curr_sum);
		DFS(root->right, curr_sum);
		--cnt[curr_sum];
	}
	int res, target;
	unordered_map<long, int> cnt;
}; // 用哈希表记录路径上全部节点的前缀和，到该节点时，检查有没有某个位置开始的路径和为目标值

int main() { }