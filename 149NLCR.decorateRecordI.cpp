// Created: 2025-06-26
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 149. 彩灯装饰记录 I
一棵圣诞树记作根节点为 root 的二叉树，节点值为该位置装饰彩灯的颜色编号。
请按照从 左 到 右 的顺序返回每一层彩灯编号。
示例 1：
	输入：root = {8,17,21,18,null,null,6}
	输出：{8,17,21,18,6}
提示：
	节点总数 <= 1000 */

class Solution {
public:
	vector<int> decorateRecord(TreeNode *root) {
		vector<int> res;
		queue<TreeNode *> que;
		if(root) que.push(root); // 防止根节点为空，出错
		while(!que.empty()) {
			TreeNode *now = que.front();
			que.pop(); // 注意pop必须放到que.size()后面
			res.push_back(now->val);
			if(now->left) que.push(now->left);
			if(now->right) que.push(now->right);
		}
		return res;
	}
}; // 广度优先遍历，这道题用DFS比较麻烦，要先获取 150ELCR 的那种数组，然后平坦化

int main() {
	Solution sol;
	TreeNode *root;
	root = createTree({ 8, 17, 21, 18, -1, -1, 6 });
	cout << sol.decorateRecord(root) << endl;
}