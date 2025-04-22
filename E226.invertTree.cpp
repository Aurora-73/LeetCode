#include "MyUtils.h"

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

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
