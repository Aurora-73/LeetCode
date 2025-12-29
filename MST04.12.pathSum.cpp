// Created: 2025-12-26
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一棵二叉树，其中每个节点都含有一个整数数值(该值或正或负)。
设计一个算法，打印节点数值总和等于某个给定值的所有路径的数量。注意，
路径不一定非得从二叉树的根节点或叶节点开始或结束，但是其方向必须向下(只能从父节点指向子节点方向)。
示例：
给定如下二叉树，以及目标和sum = 22，
              5
             / \
            4   8
           /   / \
          11  13  4
         /  \    / \
        7    2  5   1
输出：
3
解释：和为 22的路径有：{5,4,11,2}, {5,8,4,5}, {4,11,7}
提示：
	节点总数 <= 10000 */

class Solution {
public:
	int pathSum(TreeNode *root, int sum) {
		res = 0, target = sum;
		sum_cnt.clear();
		sum_cnt[0] = 1;
		dfs(root, 0);
		return res;
	}

private:
	int res, target;
	unordered_map<int, int> sum_cnt;
	void dfs(TreeNode *node, int curr_sum) {
		if(!node) return;
		curr_sum += node->val;
		auto it = sum_cnt.find(curr_sum - target);
		if(it != sum_cnt.end()) {
			res += it->second;
		}
		++sum_cnt[curr_sum];
		dfs(node->left, curr_sum);
		dfs(node->right, curr_sum);
		--sum_cnt[curr_sum];
		// unordered_map插入元素可能导致迭代器失效，所以这里的++和--不能用iterator加快
	}
};

int main() {
	Solution sol;
	TreeNode *root;
	int sum;
	root = createTree({ 5, 4, 8, 11, EMPTY_NODE, 13, 4, 7, 2, EMPTY_NODE, EMPTY_NODE, 5, 1 }),
	sum = 22;
	cout << sol.pathSum(root, sum) << endl;
}