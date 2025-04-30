// Created: 2025-04-30
#include "MyUtils.h"
#include "MyTreeNode.h"

/*114. 二叉树展开为链表
给你二叉树的根结点 root ，请你将它展开为一个单链表：
展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
展开后的单链表应该与二叉树 先序遍历 顺序相同。
 */

class Solution {
public:
	void flatten(TreeNode *root) { }
	TreeNode *preOrder(TreeNode *root, TreeNode *&pre) {
		if(!root)
			return;
		if(pre) {
			pre->right = root;
		}
	}
};

int main() {
	Solution sol;
}