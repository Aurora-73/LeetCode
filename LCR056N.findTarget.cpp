// Created: 2025-12-09
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个二叉搜索树的 根节点 root和一个整数 k , 请判断该二叉搜索树中是否存在两个节点它们的值之和等于 k。
假设二叉搜索树中节点的值均唯一。
示例 1：
	输入: root = {8,6,10,5,7,9,11}, k = 12
	输出: true
	解释: 节点 5 和节点 7 之和等于 12
示例 2：
	输入: root = {8,6,10,5,7,9,11}, k = 22
	输出: false
	解释: 不存在两个节点值之和为 22 的节点
提示：
	二叉树的节点个数的范围是{1, 10^4}.
	-10^4<= Node.val <= 10^4
	root为二叉搜索树
	-10^5<= k <= 10^5 */

class Solution1 { // 直接用二叉搜索树搜索是最差的算法
public:
	bool findTarget(TreeNode *root, int k) {
		return DFS(root, root, k);
	}

private:
	bool findval(TreeNode *root, int val, TreeNode *p) {
		if(!root) return false;
		if(root->val == val) {
			if(root != p) {
				return true;
			} else {
				return findval(root->left, val, p) || findval(root->right, val, p);
			}
		}
		if(root->val > val) {
			return findval(root->left, val, p);
		} else {
			return findval(root->right, val, p);
		}
	}
	bool DFS(TreeNode *node, TreeNode *root, int k) {
		if(!node) return false;
		if(findval(root, k - node->val, node)) {
			return true;
		}
		if(DFS(node->left, root, k)) {
			return true;
		}
		if(DFS(node->right, root, k)) {
			return true;
		}
		return false;
	}
}; // 遍历 + 二叉树搜索搜索，时间复杂度O(n * h)，空间复杂度O(n)

class Solution2 {
public:
	bool findTarget(TreeNode *root, int k) {
		vec.clear();
		Tree2Vec(root);
		int i = 0, j = vec.size() - 1;
		while(i < j) {
			int sum = vec[i] + vec[j];
			if(sum > k) {
				--j;
			} else if(sum < k) {
				++i;
			} else {
				return true;
			}
		}
		return false;
	}

private:
	vector<int> vec;
	void Tree2Vec(TreeNode *root) {
		if(!root) return;
		Tree2Vec(root->left);
		vec.push_back(root->val);
		Tree2Vec(root->right);
	}
}; // 先把全部节点的值按照中序遍历的顺序保存到数组，然后对有序数组进行两数之和，时间复杂度O(n)，空间复杂度O(n)

class Solution {
public:
	bool findTarget(TreeNode *root, int k) {
		if(!root) return false;
		if(set.count(k - root->val)) {
			return true;
		}
		set.insert(root->val);
		return findTarget(root->left, k) || findTarget(root->right, k);
	}

private:
	unordered_set<int> set;
}; // 哈希表保存，时间复杂度O(n)，空间复杂度O(n)

// 这道题直接用二叉搜索树搜索反而是最差的算法，空间复杂度也是O(n)，不如直接保存

int main() {
	Solution sol;
	TreeNode *root;
	int k;
	root = createTree({ 8, 6, 10, 5, 7, 9, 11 }), k = 22;
	cout << sol.findTarget(root, k) << endl;
	root = createTree({ 8, 6, 10, 5, 7, 9, 11 }), k = 12;
	cout << sol.findTarget(root, k) << endl;
}