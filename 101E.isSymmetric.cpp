#include "MyUtils.h"
#include "MyTreeNode.h"

class Solution {
public:
	bool isSymmetric(TreeNode *root) {
		if(!root)
			return true;
		return ismirror(root->left, root->right);
	}
	bool ismirror(TreeNode *a, TreeNode *b) {
		if(!a && !b)
			return true;
		if(!a || !b)
			return false;
		return a->val == b->val && ismirror(a->left, b->right) && ismirror(a->right, b->left);
	} // 如果是镜像，则将a->left替换掉a, b->right替换掉b仍是镜像，反之亦然
};