#include "MyUtils.h"
#include "MyTreeNode.h"

class Solution {
public:
	int maxDepth(TreeNode *root) {
		if(!root)
			return 0;
		return 1 + maxDepth(root->left) + maxDepth(root->right);
	}
};
