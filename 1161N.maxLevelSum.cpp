// Created: 2025-07-04
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 1161. 最大层内元素和
给你一个二叉树的根节点root。
设根节点位于二叉树的第 1 层，而根节点的子节点位于第 2 层，依此类推。
请返回层内元素之和 最大 的那几层（可能只有一层）的层号，并返回其中最小 的那个。
示例 1：
	输入：root = {1,7,0,7,-8,null,null}
	输出：2
	解释：
	第 1 层各元素之和为 1，
	第 2 层各元素之和为 7 + 0 = 7，
	第 3 层各元素之和为 7 + -8 = -1，
	所以我们返回第 2 层的层号，它的层内元素之和最大。
示例 2：
	输入：root = {989,null,10250,98693,-89388,null,null,null,-32127}
	输出：2
提示：
	树中的节点数在{1, 10^4}范围内
	-10^5<= Node.val <= 10^5 */

class Solution1 {
public:
	int maxLevelSum(TreeNode *root) {
		queue<TreeNode *> q;
		q.push(root);
		int max_sum = numeric_limits<int>::min(), max_level = 0, level_now = 1;
		while(!q.empty()) {
			int sum = 0, n = q.size();
			for(int i = 0; i < n; ++i) {
				TreeNode *now = q.front();
				sum += now->val;
				if(now->left) {
					q.push(now->left);
				}
				if(now->right) {
					q.push(now->right);
				}
				q.pop();
			}
			if(sum > max_sum) {
				max_sum = sum;
				max_level = level_now;
			}
			++level_now;
		}
		return max_level;
	}
};

class Solution2 {
public:
	int maxLevelSum(TreeNode *root) {
		sums.push_back(0);
		dfs(root, 1);
		int max_sum = numeric_limits<int>::min(), max_level = 0, n = sums.size();
		for(int i = 1; i < n; ++i) {
			if(sums[i] > max_sum) {
				max_sum = sums[i];
				max_level = i;
			}
		}
		return max_level;
	}

private:
	vector<int> sums;
	void dfs(TreeNode *now, unsigned level) {
		if(!now) return;
		if(sums.size() <= level) sums.push_back(0);
		sums[level] += now->val;
		dfs(now->left, level + 1);
		dfs(now->right, level + 1);
	}
};

int main() {
	Solution1 sol1;
	Solution2 sol2;
	TreeNode *root;

	root = createTree({ 1, 7, 0, 7, -8, EMPTY_NODE, EMPTY_NODE });
	cout << sol1.maxLevelSum(root) << endl;
	cout << sol2.maxLevelSum(root) << endl;

	root = createTree(
	    { 989, EMPTY_NODE, 10250, 98693, -89388, EMPTY_NODE, EMPTY_NODE, EMPTY_NODE, -32127 });
	cout << sol1.maxLevelSum(root) << endl;
	cout << sol2.maxLevelSum(root) << endl;
}