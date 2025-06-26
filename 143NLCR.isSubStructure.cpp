// Created: 2025-06-26
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 143. 子结构判断
给定两棵二叉树 tree1 和 tree2，判断 tree2 是否以 tree1 的某个节点为根的子树具有 相同的结构和节点值。
注意，空树不会是以 tree1 的某个节点为根的子树具有 相同的结构和节点值。
示例 1：
	输入：tree1 = {1,7,5}, tree2 = {6,1}
	输出：false
	解释：tree2 与 tree1 的一个子树没有相同的结构和节点值。
示例 2：
	输入：tree1 = {3,6,7,1,8}, tree2 = {6,1}
	输出：true
	解释：tree2 与 tree1 的一个子树拥有相同的结构和节点值。即 6 - > 1。
提示：
	0 <= 节点个数 <= 10000 */

class Solution {
public:
	bool isSubStructure(TreeNode *A, TreeNode *B) {
		if(!B) return false;
		return TravelA(A, B);
	}

private:
	bool TravelA(TreeNode *A, TreeNode *B) {
		if(!A) return 0;
		bool isSub = BisSubOfA(A, B);
		if(!isSub) isSub = TravelA(A->left, B);
		if(!isSub) isSub = TravelA(A->right, B);
		return isSub;
	}
	bool BisSubOfA(TreeNode *A, TreeNode *B) {
		if(!B) return true;
		if(!A || A->val != B->val) return false;
		return BisSubOfA(A->left, B->left) && BisSubOfA(A->right, B->right);
	}
};

int main() {
	Solution sol;
	TreeNode *A, *B;
	A = createTree({ 1, 7, 5 });
	B = createTree({ 6, 1 });
	cout << sol.isSubStructure(A, B) << endl; // 0
	A = createTree({ 3, 6, 7, 1, 8 });
	B = createTree({ 6, 1 });
	cout << sol.isSubStructure(A, B) << endl; // 1
}