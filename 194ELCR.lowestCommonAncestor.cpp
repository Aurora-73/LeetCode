// Created: 2025-06-27
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 194. 二叉树的最近公共祖先
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，
满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
例如，给定如下二叉树: root ={3,5,1,6,2,0,8,null,null,7,4}
示例 1：
	输入：root = {3,5,1,6,2,0,8,null,null,7,4}, p = 5, q = 1
	输出：3
	解释：节点 5 和节点 1 的最近公共祖先是节点 3。
示例2：
	输入：root = {3,5,1,6,2,0,8,null,null,7,4}, p = 5, q = 4
	输出：5
	解释：节点 5 和节点 4 的最近公共祖先是节点 5。因为根据定义最近公共祖先节点可以为节点本身。
	说明：
	所有节点的值都是唯一的。
	p、q 为不同节点且均存在于给定的二叉树中。 */

class Solution1 {
public:
	TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
		vector<TreeNode *> path, path2;
		TreeNode *curr = root;
		TreeNode *lastVisited = nullptr;

		while(curr || !path.empty()) {
			while(curr) {
				path.push_back(curr);
				curr = curr->left;
			}
			TreeNode *node = path.back();
			// 如果右子树存在且没访问过，转向右子树
			if(node->right && node->right != lastVisited) {
				curr = node->right;
			} else {
				// 否则访问当前节点，并记录为“最近访问”
				if(node == p || node == q) {
					if(path2.empty()) {
						path2 = path;
					} else {
						break;
					}
				}
				lastVisited = node;
				path.pop_back();
			}
		} // 非递归后序遍历

		int min_size = min(path.size(), path2.size()), i = 0;
		while(i < min_size && path[i] == path2[i]) ++i;
		return path[i - 1];
	}
}; // 非递归后序遍历遍历到p q节点时的最后一个公共节点

class Solution2 {
public:
	TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
		vector<TreeNode *> pathP, pathQ;

		// 找到从根到p和q的路径
		findPath(root, p, pathP);
		findPath(root, q, pathQ);

		// 找到最后一个公共节点
		int min_size = min(pathP.size(), pathQ.size()), i = 0;
		while(i < min_size && pathP[i] == pathQ[i]) ++i;
		return pathP[i - 1];
	}

private:
	bool findPath(TreeNode *root, TreeNode *target, vector<TreeNode *> &path) {
		if(!root) return false;

		path.push_back(root);

		if(root == target) return true;

		if(findPath(root->left, target, path) || findPath(root->right, target, path)) {
			return true;
		}

		path.pop_back(); // 回溯
		return false;
	}
}; // 递归遍历，保存路径

class Solution {
public:
	TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
		if(!root || root == p || root == q) return root;

		auto left = lowestCommonAncestor(root->left, p, q);
		auto right = lowestCommonAncestor(root->right, p, q);

		if(left && right) return root;
		return left ? left : right;
	}
};

int main() {
	Solution sol;
}