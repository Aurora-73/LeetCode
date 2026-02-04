#include "MyTreeNode.h"
#include "MyUtils.hpp"

/* 给定一个二叉树 root，返回其最大深度。
二叉树的 最大深度 是指从根节点到最远叶子节点的最长路径上的节点数。
示例 1：
	输入：root = {3,9,20,null,null,15,7}
	输出：3
示例 2：
	输入：root = {1,null,2}
	输出：2
提示：
	树中节点的数量在{0, 10^4}区间内。
	-100 <= Node.val <= 100 */

class Solution {
public:
	int maxDepth(TreeNode *root) {
		if(!root) return 0;
		return 1 + maxDepth(root->left) + maxDepth(root->right);
	}
};

int main() {
	Solution sol;
	TreeNode *root;

	root = createTree({ 3, 9, 20, EMPTY_NODE, EMPTY_NODE, 15, 7 });
	cout << sol.maxDepth(root) << endl;

	root = createTree({ 1, EMPTY_NODE, 2 });
	cout << sol.maxDepth(root) << endl;
}
