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
	void flatten(TreeNode *root) {
		if(!root)
			return;
		vec.clear();
		for(int i = 1; i < vec.size(); i++) {
			vec[i - 1]->right = vec[i];
			vec[i - 1]->left = nullptr;
		}
	}
	void preOrder(TreeNode *root) {
		if(!root)
			return;
		vec.push_back(root);
		preOrder(root->left);
		preOrder(root->right);
	}

private:
	vector<TreeNode *> vec;
};

int main() {
	Solution sol;
}