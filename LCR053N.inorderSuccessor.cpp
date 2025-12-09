// Created: 2025-12-08
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一棵二叉搜索树和其中的一个节点 p，找到该节点在树中的中序后继。
如果节点没有中序后继，请返回 null。
节点p的后继是值比p.val大的节点中键值最小的节点，即按中序遍历的顺序节点 p 的下一个节点。
示例 1：
	输入：root = {2,1,3}, p = 1
	输出：2
	解释：这里 1 的中序后继是 2。请注意 p 和返回值都应是 TreeNode 类型。
示例2：
	输入：root = {5,3,6,2,4,null,null,1}, p = 6
	输出：null
	解释：因为给出的节点没有中序后继，所以答案就返回 null 了。
提示：
	树中节点的数目在范围 {1, 10^4} 内。
	-10^5 <= Node.val <= 10^5
	树中各节点的值均保证唯一。 */

class Solution1 {
public:
	TreeNode *inorderSuccessor(TreeNode *root, TreeNode *pp) {
		res = nullptr;
		isOk = false;
		p = pp;
		inorder(root);
		return res;
	}
	void inorder(TreeNode *root) {
		if(!root) {
			return;
		}
		inorder(root->left);
		if(isOk) {
			res = root;
			isOk = false;
		}
		if(p == root) {
			isOk = true;
		}
		inorder(root->right);
	}

private:
	bool isOk;
	TreeNode *res, *p;
};

class Solution {
public:
	TreeNode *inorderSuccessor(TreeNode *root, TreeNode *p) {
		if(root == nullptr || p == nullptr) return nullptr;

		// 情况一：如果 p 有右子树，后继就是右子树的最左节点
		if(p->right) {
			TreeNode *cur = p->right;
			while(cur->left) cur = cur->left;
			return cur;
		}

		// 情况二：p 没有右子树，后继是从 root 到 p 路径上最后一个比 p 大的节点（最低的大于 p 的祖先）
		// 因为根据中序遍历的规则，如果p没有右子树，中序遍历访问到 p 后会向上回溯，直到遇到第一个把 p 放在其左子树中的祖先
		TreeNode *successor = nullptr;
		TreeNode *cur = root;
		while(cur != p) {
			if(p->val < cur->val) {
				// cur 有可能是后继，向左继续找更接近 p 的候选
				successor = cur;
				cur = cur->left;
			} else {
				// cur 小于等于 p，不可能是后继，向右寻找 p
				cur = cur->right;
			}
		}
		return successor;
	}
};

int main() { }