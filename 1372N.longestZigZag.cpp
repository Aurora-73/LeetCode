// Created: 2025-07-05
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 1372. 二叉树中的最长交错路径
给你一棵以root为根的二叉树，二叉树中的交错路径定义如下：
	选择二叉树中 任意节点和一个方向（左或者右）。
	如果前进方向为右，那么移动到当前节点的的右子节点，否则移动到它的左子节点。
	改变前进方向：左变右或者右变左。
	重复第二步和第三步，直到你在树中无法继续移动。
交错路径的长度定义为：访问过的节点数目 - 1（单个节点的路径长度为 0 ）。
请你返回给定树中最长 交错路径的长度。
示例 1：
	输入：root = {1,EMPTY_NODE,1,1,1,EMPTY_NODE,EMPTY_NODE,1,1,EMPTY_NODE,1,EMPTY_NODE,EMPTY_NODE,EMPTY_NODE,1,EMPTY_NODE,1}
	输出：3
	解释：蓝色节点为树中最长交错路径（右 -> 左 -> 右）。
示例 2：
	输入：root = {1,1,1,EMPTY_NODE,1,EMPTY_NODE,EMPTY_NODE,1,1,EMPTY_NODE,1}
	输出：4
	解释：蓝色节点为树中最长交错路径（左 -> 右 -> 左 -> 右）。
示例 3：
	输入：root = {1}
	输出：0
提示：
	每棵树最多有50000个节点。
	每个节点的值在{1, 100} 之间。 */

class Solution1 {
public:
	int longestZigZag(TreeNode *root) {
		res = 0;
		dfs(root, 0);
		dfs(root, 1);
		return res - 1;
	}

private:
	int res;
	int dfs(TreeNode *root, bool IsLeft) {
		if(!root) return 0;
		int continueCnt = dfs(IsLeft ? root->right : root->left, !IsLeft) + 1;
		int nowBeginCnt = dfs(IsLeft ? root->left : root->right, IsLeft) + 1;
		res = max({ continueCnt, nowBeginCnt, res });
		return continueCnt; // 只返回继续的
	}
}; // 有很多重复遍历，很慢，指数级复杂度

class Solution2 {
public:
	int longestZigZag(TreeNode *root) {
		if(!root) return 0;
		maxLen = 0;
		dfs(root, 0, 0);
		dfs(root, 1, 0);
		return maxLen - 1;
	}

private:
	int maxLen;
	void dfs(TreeNode *o, bool dir, int len) {
		maxLen = max(maxLen, len + 1);
		if(!dir) {
			if(o->left) dfs(o->left, 1, len + 1);
			if(o->right) dfs(o->right, 0, 1);
		} else {
			if(o->right) dfs(o->right, 0, len + 1);
			if(o->left) dfs(o->left, 1, 1);
		}
	} // 不需要返回值，用参数传递已经遍历的长度
}; // 没有重复遍历，时间复杂度 O(n)

class Solution {
public:
	int longestZigZag(TreeNode *root) {
		int res = 0;
		helper(root, res);
		return res - 1;
	}

private:
	// 返回 pair<从左走的最长ZigZag路径, 从右走的最长ZigZag路径>
	pair<int, int> helper(TreeNode *curr, int &res) {
		if(curr == nullptr) return { 0, 0 }; // 注意：从空节点走一步回来才是0，所以是 -1

		auto left = helper(curr->left, res);
		auto right = helper(curr->right, res);

		// 从当前节点往左走的ZigZag长度 = 右孩子走的最大路径 + 1
		// 从当前节点往右走的ZigZag长度 = 左孩子走的最大路径 + 1
		pair<int, int> parent = { left.second + 1, right.first + 1 };

		// 更新全局最大值
		res = max(res, max(parent.first, parent.second));

		return parent;
	}
}; // 每个节点只递归一次，递归时一次性计算并返回“从左走”和“从右走”的最长交错路径，所有信息都在一次遍历中完成，时间复杂度O(N)。

int main() {
	Solution sol;
	TreeNode *root;
	root = createTree({ 1,
	    EMPTY_NODE,
	    1,
	    1,
	    1,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    1,
	    1,
	    EMPTY_NODE,
	    1,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    1,
	    EMPTY_NODE,
	    1 });
	cout << sol.longestZigZag(root) << endl; // 3
	root = createTree({ 1, 1, 1, EMPTY_NODE, 1, EMPTY_NODE, EMPTY_NODE, 1, 1, EMPTY_NODE, 1 });
	cout << sol.longestZigZag(root) << endl; // 4
	root = createTree({ 1 });
	cout << sol.longestZigZag(root) << endl; // 0
}