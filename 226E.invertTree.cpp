#include "MyUtils.h"
#include "MyTreeNode.h"

class Solution {
public:
	TreeNode *invertTree(TreeNode *root) {
		if(root == nullptr)
			return nullptr;
		swap(root->left, root->right);
		invertTree(root->left);
		invertTree(root->right);
		return root;
	}
};

class Solution {
public:
	TreeNode *invertTree(TreeNode *root) {
		if(root == nullptr)
			return nullptr;
		invertTree(root->left);
		swap(root->left, root->right);
		invertTree(root->left);
		return root;
	}
};

class Solution {
public:
	TreeNode *invertTree(TreeNode *root) {
		if(root == nullptr)
			return nullptr;
		invertTree(root->left);
		invertTree(root->right);
		swap(root->left, root->right);
		return root;
	}
};
