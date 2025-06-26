// Created: 2025-06-26
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 150. 彩灯装饰记录 II
一棵圣诞树记作根节点为 root 的二叉树，节点值为该位置装饰彩灯的颜色编号。
请按照从左到右的顺序返回每一层彩灯编号，每一层的结果记录于一行。
示例 1：
	输入：root = {8,17,21,18,null,null,6}
	输出：{{8},{17,21},{18,6}}
提示：
	节点总数 <= 1000 */

class Solution1 {
public:
	vector<vector<int>> decorateRecord(TreeNode *root) {
		vector<vector<int>> res;
		dfs(root, res, 0);
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
}; // 深度优先遍历

class Solution2 {
public:
	vector<vector<int>> decorateRecord(TreeNode *root) {
		vector<vector<int>> res;
		queue<TreeNode *> que;
		if(root) que.push(root); // 防止根节点为空，出错
		int levelLen = 0;
		while(!que.empty()) {
			TreeNode *now = que.front();
			if(levelLen == 0) {
				res.push_back({});
				levelLen = que.size();
			}
			que.pop(); // 注意pop必须放到que.size()后面
			res.back().push_back(now->val);
			if(now->left) que.push(now->left);
			if(now->right) que.push(now->right);
			--levelLen;
		}
		return res;
	}
}; // 广度优先遍历，注意如何获取每层长度

class Solution {
public:
	vector<vector<int>> decorateRecord(TreeNode *root) {
		if(!root) return {};
		vector<vector<int>> res;
		queue<TreeNode *> que;
		que.push(root);
		while(!que.empty()) {
			int levelSize = que.size();
			res.push_back({});
			res.back().reserve(levelSize);
			for(int i = 0; i < levelSize; ++i) {
				TreeNode *now = que.front();
				que.pop();
				res.back().push_back(now->val);
				if(now->left) que.push(now->left);
				if(now->right) que.push(now->right);
			}
		}
		return res;
	}
}; // 层序遍历，常见写法

int main() {
	Solution sol;
	TreeNode *root;
	root = createTree({ 8, 17, 21, 18, -1, -1, 6 });
	cout << sol.decorateRecord(root) << endl;
}