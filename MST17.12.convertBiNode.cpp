// Created: 2026-01-05
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 二叉树数据结构TreeNode可用来表示单向链表（其中left置空，right为下一个链表节点）。
实现一个方法，把二叉搜索树转换为单向链表，要求依然符合二叉搜索树的性质，转换操作应是原址的，也就是在原始的二叉搜索树上直接修改。
返回转换后的单向链表的头节点。
注意：本题相对原题稍作改动
	示例：
	输入： {4,2,5,1,3,null,6,0}
	输出： {0,null,1,null,2,null,3,null,4,null,5,null,6}
提示：
	节点数量不会超过 100000。 */

class Solution {
public:
	TreeNode *convertBiNode(TreeNode *root) {
		TreeNode dummy(-1);
		TreeNode *prev = &dummy;
		dfs(root, prev);
		return dummy.right;
	}

private:
	void dfs(TreeNode *root, TreeNode *&prev) {
		if(!root) return;
		dfs(root->left, prev);
		prev->right = root;
		root->left = nullptr; // 注意这里，如果用的是prev，需要在主函数中重新清理一次
		prev = root;
		dfs(root->right, prev);
	}
};

int main() {
	Solution sol;
	TreeNode *root;
	root = createTree({ 4, 2, 5, 1, 3, EMPTY_NODE, 6, 0 });
	cout << sol.convertBiNode(root) << endl;
}