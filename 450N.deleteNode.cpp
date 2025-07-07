// Created: 2025-07-06
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 450. 删除二叉搜索树中的节点
给定一个二叉搜索树的根节点 root 和一个值 key，删除二叉搜索树中的key对应的节点，并保证二叉搜索树的性质不变。
返回二叉搜索树（有可能被更新）的根节点的引用。
一般来说，删除节点可分为两个步骤：
	首先找到需要删除的节点；
	如果找到了，删除它。
示例 1:
	输入：root = {5,3,6,2,4,null,7}, key = 3
	输出：{5,4,6,2,null,null,7}
	解释：给定需要删除的节点值是 3，所以我们首先找到 3 这个节点，然后删除它。
	一个正确的答案是 {5,4,6,2,null,null,7}, 如下图所示。
	另一个正确答案是 {5,2,6,null,4,null,7}。
示例 2:
	输入: root = {5,3,6,2,4,null,7}, key = 0
	输出: {5,3,6,2,4,null,7}
	解释: 二叉树不包含值为 0 的节点
示例 3:
	输入: root = {}, key = 0
	输出: {}
提示:
	节点数的范围{0, 10^4}.
	-10^5<= Node.val <= 10^5
	节点值唯一
	root是合法的二叉搜索树
	-10^5<= key <= 10^5
	进阶： 要求算法时间复杂度为O(h)，h 为树的高度。 */

class Solution {
public:
	TreeNode *deleteNode(TreeNode *root, int key) {
		if(!root) return nullptr;
		if(root->val > key) {
			root->left = deleteNode(root->left, key);
		} else if(root->val < key) {
			root->right = deleteNode(root->right, key);
		} else {
			if(!root->left) {
				return root->right;
			} else if(!root->right) {
				return root->left;
			} else {
				TreeNode *now = root->left;
				while(now->right) {
					now = now->right;
				}
				now->right = root->right;
				return root->left;
				// 复杂情况用 左子树的最右节点 接上 右子树，再以 左子树顶 替原节点。
			}
		}
		return root;
	}
};
/* 递归实现：递归时将返回值设置为对应的孩子节点，先递归到目标节点，然后
    如果当前节点没有左孩子或右孩子，则将该节点的另一个孩子替换为当前节点，
    否则寻找左子树的最右节点或者右孩子的最左节点，然后将另一个子树移植到该节点的对应孩子处，最后以根节点的左/右孩子替代根节点 
    这种解法不需要记录父节点，直接使用返回值进行赋值即可完成节点的替换 */

class Solution {
public:
	TreeNode *deleteNode(TreeNode *root, int key) {
		// 1. 构造 dummy 方便统一处理 root 被删除的情况
		TreeNode dummy(0);
		dummy.left = root;

		// 2. 查找待删节点 curr 及其父节点 parent
		TreeNode *parent = &dummy;
		TreeNode *curr = root;
		bool isLeftChild = true; // curr 是 parent 的左子节点还是右子节点
		while(curr && curr->val != key) {
			parent = curr;
			if(key < curr->val) {
				curr = curr->left;
				isLeftChild = true;
			} else {
				curr = curr->right;
				isLeftChild = false;
			}
		}
		if(!curr) return root;

		TreeNode *replacer = nullptr;

		if(!curr->left) {
			replacer = curr->right;
		} else if(!curr->right) {
			replacer = curr->left;
		} else {
			TreeNode *replacerParent = curr;
			replacer = curr->left;
			while(replacer->right) {
				replacerParent = replacer;
				replacer = replacer->right;
			}
			// 将 pred 从原来位置摘除，并把它的左子树接到 predParent
			if(replacerParent->right == replacer) {
				replacerParent->right = replacer->left;
			} else {
				replacerParent->left = replacer->left;
			}
			replacer->left = curr->left;
			replacer->right = curr->right;
		}

		if(isLeftChild)
			parent->left = replacer;
		else
			parent->right = replacer;

		return dummy.left;
	}
};

/* 迭代解法：首先找到待删除节点和待删除节点的父节点，然后寻找替代被删除节点的节点，
        注意同时有左右子树的情况，然后将替代用的节点挂回到父节点处
        可以设置虚拟节点应对根节点被删除的情况 */

/* 注意者两个解法对于左右子树均存在的情况的处理方法不一样，
递归版：直接把整棵左子树（含前驱）当成新子树返回，不需要显式 剪断 ，因为旧的根节点和它的原右子树被放到前驱 now->right 后，旧根自然脱离；
迭代版：先把前驱节点在左子树里的旧位置 空 出来，再把它移植到被删节点位置，逻辑上更像链表的节点搬运。 */

int main() {
	Solution sol;
}