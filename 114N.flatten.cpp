// Created: 2025-04-30
#include "MyUtils.h"
#include "MyTreeNode.h"

/*114. 二叉树展开为链表
给你二叉树的根结点 root ，请你将它展开为一个单链表：
展开后的单链表应该同样使用 TreeNode ，其中 right 子指针指向链表中下一个结点，而左子指针始终为 null 。
展开后的单链表应该与二叉树 先序遍历 顺序相同。
 */

class Solution1 {
public:
	void flatten(TreeNode *root) {
		if(!root)
			return;
		vec.clear();
		preOrder(root);
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

class Solution2 {
public:
	void flatten(TreeNode *root) {
		while(root) {
			TreeNode *right = root->right;
			if(root->left) {
				root->right = root->left;
				root->left = nullptr;
				if(right) {
					TreeNode *end = root;
					while(end->right) {
						end = end->right;
					}
					end->right = right;
				}
			}
			root = root->right;
		}
	}
};
/*将左子树插入到右子树的地方
将原来的右子树接到左子树的最右边节点
考虑新的右子树的根节点，一直重复上边的过程，直到新的右子树为 null*/

class Solution3 {
public:
	void flatten(TreeNode *root) {
		if(!root)
			return;
		flatten(root->left);
		flatten(root->right);
		TreeNode *right = root->right;
		root->right = root->left;
		root->left = nullptr;
		while(root->right) {
			root = root->right;
		}
		root->right = right;
	}
};
/*递归解法*/

/*关键在于先序遍历的时候右子树都是在左子树后面，因此可以把右子树直接放到左子树最后一个的右边*/
int main() {
	Solution1 sol;
}