// Created: 2025-05-01
#include "MyTreeNode.h"
#include "MyUtils.hpp"

/* 给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
百度百科中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，
满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”
示例 1：
	输入：root = {3,5,1,6,2,0,8,null,null,7,4}, p = 5, q = 1
	输出：3
	解释：节点 5 和节点 1 的最近公共祖先是节点 3。
示例 2：
	输入：root = {3,5,1,6,2,0,8,null,null,7,4}, p = 5, q = 4
	输出：5
	解释：节点 5 和节点 4 的最近公共祖先是节点 5。因为根据定义最近公共祖先节点可以为节点本身。
示例 3：
	输入：root = {1,2}, p = 1, q = 2
	输出：1
提示：
	树中节点数目在范围 {2, 10^5} 内。
	-10^9 <= Node.val <= 10^9
	所有 Node.val 互不相同。
	p != q
	p 和 q 均存在于给定的二叉树中。 */

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
		TreeNode *lc = lowestCommonAncestor(root->left, p, q);
		TreeNode *rc = lowestCommonAncestor(root->right, p, q);
		if(lc && rc) {
			return root;
		}
		return lc ? lc : rc;
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