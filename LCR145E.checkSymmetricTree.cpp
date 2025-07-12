// Created: 2025-06-26
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 145. 判断对称二叉树
请设计一个函数判断一棵二叉树是否 轴对称。
示例 1：
	输入：root = {6,7,7,8,9,9,8}
	输出：true
	解释：从图中可看出树是轴对称的。
示例 2：
	输入：root = {1,2,2,null,3,null,3}
	输出：false
	解释：从图中可看出最后一层的节点不对称。
提示：
	0 <= 节点个数 <= 1000 */

class Solution {
public:
	bool checkSymmetricTree(TreeNode *root) {
		if(!root) return true;
		return isEqual(root->left, root->right);
	}

private:
	bool isEqual(TreeNode *A, TreeNode *B) {
		if(!A && !B) return true;
		if(!A || !B || A->val != B->val) return false;
		return isEqual(A->left, B->right) && isEqual(A->right, B->left);
	}
};

int main() {
	Solution sol;
	TreeNode *root;
	root = createTree({ 6, 7, 7, 8, 9, 9, 8 }); // true
	cout << sol.checkSymmetricTree(root) << endl;
	root = createTree({ 1, 2, 2, EMPTY_NODE, 3, EMPTY_NODE, 3 }); // false
	cout << sol.checkSymmetricTree(root) << endl;
}