// Created: 2025-12-25
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 设计一个算法，找出二叉搜索树中指定节点的“下一个”节点（也即中序后继）。
如果指定节点没有对应的“下一个”节点，则返回null。
示例 1：
	输入：root = {2,1,3}, p = 1
	  2
	 / \
	1   3
	输出：2
示例 2：
	输入：root = {5,3,6,2,4,null,null,1}, p = 6
	      5
	     / \
	    3   6
	   / \
	  2   4
	 /   
	1
	输出：null */

class Solution {
public:
	TreeNode *inorderSuccessor(TreeNode *root, TreeNode *p) {
		if(p->right) {
			TreeNode *res = p->right;
			while(res->left) {
				res = res->left;
			}
			return res;
		} else {
			TreeNode *res = nullptr;
			while(root != p) {
				if(root->val > p->val) {
					res = root;
					root = root->left;
				} else {
					root = root->right;
				}
			}
			return res;
		} // 回朔到最后一个把他当做左子树上节点的父节点
	}
}; // 如果p节点有右子树，则中序后继是他右子树上的最左节点
// 如果p节点没有右子树，则中序后继是最后一个把他当做左子树上的节点的祖先节点

int main() { }