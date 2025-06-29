// Created: 2025-06-28
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 124. 推理二叉树
某二叉树的先序遍历结果记录于整数数组 preorder，它的中序遍历结果记录于整数数组 inorder。
请根据 preorder 和 inorder 的
提示构造出这棵二叉树并返回其根节点。
注意：preorder 和 inorder 中均不含重复数字。
示例 1：
	输入: preorder = {3,9,20,15,7}, inorder = {9,3,15,20,7}
	输出: {3,9,20,null,null,15,7}
示例 2:
	输入: preorder = {-1}, inorder = {-1}
	输出: {-1}
提示:
	1 <= preorder.length <= 3000
	inorder.length == preorder.length
	-3000 <= preorder{i}, inorder{i} <= 3000
	inorder 均出现在 preorder
	preorder 保证 为二叉树的前序遍历序列
	inorder 保证 为二叉树的中序遍历序列 */

class Solution1 {
	using iter = vector<int>::iterator;

public:
	TreeNode *deduceTree(vector<int> &preorder, vector<int> &inorder) {
		iter preBegin = preorder.begin();
		return TreeCreat(preBegin, preorder.end(), inorder.begin(), inorder.end());
	}

private:
	TreeNode *TreeCreat(iter &preBegin, iter preEnd, iter inBegin, iter inEnd) {
		if(inBegin == inEnd || preBegin == preEnd) {
			return nullptr;
		}
		auto it = std::find(inBegin, inEnd, *preBegin);
		TreeNode *now = new TreeNode(*preBegin);
		++preBegin;
		now->left = TreeCreat(preBegin, preEnd, inBegin, it);
		now->right = TreeCreat(preBegin, preEnd, ++it, inEnd);
		return now;
	}
};

class Solution {
	using iter = vector<int>::iterator;

public:
	TreeNode *deduceTree(vector<int> &preorder, vector<int> &inorder) {
		int n = inorder.size();
		for(int i = 0; i < n; ++i) {
			inorder_map[inorder[i]] = i;
		}

		iter preBegin = preorder.begin();
		return TreeCreat(preBegin, preorder.end(), 0, n);
	}

private:
	unordered_map<int, int> inorder_map;
	TreeNode *TreeCreat(iter &preBegin, iter preEnd, int inStart, int inEnd) {
		if(inStart >= inEnd || preBegin == preEnd) {
			return nullptr;
		}
		int rootVal = *preBegin;
		int rootIndex = inorder_map[rootVal];
		TreeNode *root = new TreeNode(rootVal);
		++preBegin;
		root->left = TreeCreat(preBegin, preEnd, inStart, rootIndex);
		root->right = TreeCreat(preBegin, preEnd, rootIndex + 1, inEnd);
		return root;
	}
};

int main() {
	Solution sol;
	vector<int> preorder, inorder;
	preorder = { 3, 9, 20, 15, 7 }, inorder = { 9, 3, 15, 20, 7 };
	cout << sol.deduceTree(preorder, inorder) << endl;
	preorder = { -1 }, inorder = { -1 };
	cout << sol.deduceTree(preorder, inorder) << endl;
}