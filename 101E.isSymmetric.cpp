#include "MyTreeNode.h"
#include "MyUtils.hpp"

class Solution {
public:
	bool isSymmetric(TreeNode *root) {
		if(!root) return true;
		return ismirror(root->left, root->right);
	}
	bool ismirror(TreeNode *a, TreeNode *b) {
		if(!a && !b) return true;
		if(!a || !b) return false;
		return a->val == b->val && ismirror(a->left, b->right) && ismirror(a->right, b->left);
	} // 如果是镜像，则将a->left替换掉a, b->right替换掉b仍是镜像，反之亦然
};

int main() {
	Solution s;
	TreeNode *root = createTree({ 1, 2, 2, 3, 4, 4, 3 });
	cout << root << endl;
	std::cout << "Is symmetric: " << std::boolalpha << s.isSymmetric(root) << std::endl;
	return 0;
}