// Created: 2025-07-05
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 872. 叶子相似的树
请考虑一棵二叉树上所有的叶子，这些叶子的值按从左到右的顺序排列形成一个叶值序列。
举个例子，如上图所示，给定一棵叶值序列为(6, 7, 4, 9, 8)的树。
如果有两棵二叉树的叶值序列是相同，那么我们就认为它们是叶相似的。
如果给定的两个根结点分别为root1 和root2的树是叶相似的，则返回true；否则返回 false。
示例 1：
	输入：root1 = {3,5,1,6,2,9,8,EMPTY_NODE,EMPTY_NODE,7,4}, root2 = {3,5,1,6,7,4,2,EMPTY_NODE,EMPTY_NODE,EMPTY_NODE,EMPTY_NODE,EMPTY_NODE,EMPTY_NODE,9,8}
	输出：true
示例 2：
	输入：root1 = {1,2,3}, root2 = {1,3,2}
	输出：false
提示：
	给定的两棵树结点数在{1, 200} 范围内
	给定的两棵树上的值在{0, 200} 范围内 */

class Solution {
public:
	bool leafSimilar(TreeNode *root1, TreeNode *root2) {
		vector<int> leafs;
		int readId = -1;
		dfs(root1, leafs, readId);
		readId = 0;
		if(!dfs(root2, leafs, readId)) return false;
		return readId == int(leafs.size());
	}

private:
	bool dfs(TreeNode *root, vector<int> &leafs, int &readId) {
		if(!root) return true;
		if(!root->left && !root->right) {
			if(readId == -1) {
				leafs.push_back(root->val);
				return true;
			} else {
				if(leafs[readId++] != root->val) return false;
			}
		}
		if(!dfs(root->left, leafs, readId)) return false;
		if(!dfs(root->right, leafs, readId)) return false;
		return true;
	} // dfs 可以进行赋值或者验证。
};

int main() {
	Solution sol;
	TreeNode *root1, *root2;
	root1 = createTree({ 3, 5, 1, 6, 2, 9, 8, EMPTY_NODE, EMPTY_NODE, 7, 4 });
	root2 = createTree({ 3,
	    5,
	    1,
	    6,
	    7,
	    4,
	    2,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    9,
	    8 });
	cout << sol.leafSimilar(root1, root2) << endl; // true
	root1 = createTree({ 1, 2, 3 });
	root2 = createTree({ 1, 3, 2 });
	cout << sol.leafSimilar(root1, root2) << endl; // false
}