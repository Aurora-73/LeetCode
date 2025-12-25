// Created: 2025-12-25
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 设计并实现一个算法，找出二叉树中某两个节点的第一个共同祖先。
不得将其他的节点存储在另外的数据结构中。注意：这不一定是二叉搜索树。
例如，给定如下二叉树: root = {3,5,1,6,2,0,8,null,null,7,4}
    3
   / \
  5   1
 / \ / \
6  2 0  8
  / \
 7   4
示例 1：
	输入：root = {3,5,1,6,2,0,8,null,null,7,4}, p = 5, q = 1
	输出：3
	解释：节点 5 和节点 1 的最近公共祖先是节点 3。
示例 2：
	输入：root = {3,5,1,6,2,0,8,null,null,7,4}, p = 5, q = 4
	输出：5
	解释：节点 5 和节点 4 的最近公共祖先是节点 5。因为根据定义最近公共祖先节点可以为节点本身。
提示：
	所有节点的值都是唯一的。
	p、q 为不同节点且均存在于给定的二叉树中。 */

class Solution1 {
public:
	TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
		res = nullptr;
		dfs(root, p, q);
		return res;
	}

private:
	TreeNode *res;
	bool dfs(TreeNode *root, TreeNode *p, TreeNode *q) {
		if(!root || res) return false;
		bool l = dfs(root->left, p, q);
		bool r = dfs(root->right, p, q);
		bool curr = (root == p || root == q);
		if((l && r) || (curr && (l || r))) {
			res = root;
		}
		return l || r || curr;
	}
};

class Solution {
public:
	TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
		if(!root || root == p || root == q) return root;
		TreeNode *left = lowestCommonAncestor(root->left, p, q);
		TreeNode *right = lowestCommonAncestor(root->right, p, q);
		if(left && right) return root;
		return left ? left : right;
	}
};
/* 如果root是p或q，可以直接返回root，不需要继续递归，因为这时有两种可能：
	1、如果另一个节点是root的子节点，那结果就是root，且root的上层节点不会修改这次返回的值，会将它一直向上传递
	2、如果另一个节点不是root的子节点，则上层节点必定有一个是结果，且这个节点会向上层返回正确的值 */
/* 本质上，该题目有两种情况，
	情况1: 两个节点p,q分布于最深父公共祖先（LCA）的两侧。
	情况2:两个节点中的较浅节点p就为LCA，此时另一个节点q在该节点之下
从自底向上的视角理解：
	首先确定返回值，当递归到某个节点，该节点符合（root == p or root == q）的条件就向上返回，这个节点是一个潜在的LCA候选者（Candidate）。
	候选者的意思是它有可能就是我们在找的LCA，也有可能并不是，但是和None不一样，它是有用的，想不明白的话可以先不用去理解这部分。
	当递归到None，也向上返回，说明该侧已经搜寻完毕，不可能存在任何候选者。
	情况2的对应：该Candidate向上返回时，一路畅通无阻（另一侧始终是None），一直返回到根节点。说明刚刚的Candidate即为在寻找的LCA。
	情况1的对应: 该Candidate向上返回到某个节点Node，发现如果另一侧也返回了一个Candidate。说明Node才是真正的LCA。*/

int main() { }