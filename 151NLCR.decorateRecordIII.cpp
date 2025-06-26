// Created: 2025-06-26
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 151. 彩灯装饰记录 III
一棵圣诞树记作根节点为 root 的二叉树，节点值为该位置装饰彩灯的颜色编号。
请按照如下规则记录彩灯装饰结果：
	第一层按照从左到右的顺序记录
	除第一层外每一层的记录顺序均与上一层相反。即第一层为从左到右，第二层为从右到左。
示例 1：
	输入：root = {8,17,21,18,null,null,6}
	输出：{{8},{21,17},{18,6}}
提示：
	节点总数 <= 1000 */

class Solution1 {
public:
	vector<vector<int>> decorateRecord(TreeNode *root) {
		vector<vector<int>> res;
		dfs(root, res, 0);
		int n = res.size();
		for(int i = 1; i < n; i += 2) {
			std::reverse(res[i].begin(), res[i].end());
		}
		return res;
	}

private:
	void dfs(TreeNode *root, vector<vector<int>> &res, unsigned deepth) {
		if(!root) return;
		if(deepth >= res.size()) {
			res.push_back({});
		}
		res[deepth].push_back(root->val);
		dfs(root->left, res, deepth + 1);
		dfs(root->right, res, deepth + 1);
	}
}; // 深度优先遍历，然后reverse

class Solution {
public:
	vector<vector<int>> decorateRecord(TreeNode *root) {
		vector<vector<int>> res;
		queue<TreeNode *> que;
		if(root) que.push(root);
		while(!que.empty()) {
			int levelSize = que.size();
			res.emplace_back(levelSize); // 直接生成指定长度的数组
			bool l2r = res.size() % 2;   // 是否是从左往右
			for(int i = 0; i < levelSize; ++i) {
				root = que.front(), que.pop();
				res.back()[l2r ? i : levelSize - i - 1] = root->val;
				if(root->left) que.push(root->left);
				if(root->right) que.push(root->right);
			}
		}
		return res;
	}
}; // 层序遍历，计算下标值，赋值而不是push_back

int main() {
	Solution sol;
	TreeNode *root;
	root = createTree({ 8, 17, 21, 18, -1, -1, 6 });
	cout << sol.decorateRecord(root) << endl;
}