// Created: 2025-12-26
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 检查子树。
你有两棵非常大的二叉树：T1，有几万个节点；T2，有几万个节点。设计一个算法，判断 T2 是否为 T1 的子树。
如果 T1 有这么一个节点 n，其子树与 T2 一模一样，则 T2 为 T1 的子树，
也就是说，从节点 n 处把树砍断，得到的树与 T2 完全相同。
注意：此题相对书上原题略有改动。
示例 1：
	 输入：t1 = {1, 2, 3}, t2 = {2}
	 输出：true
示例 2：
	 输入：t1 = {1, null, 2, 4}, t2 = {3, 2}
	 输出：false
提示：
	树的节点数目范围为 {0, 20000}。 */

class Solution1 {
public:
	bool checkSubTree(TreeNode *t1, TreeNode *t2) {
		if(!t2) return 1;
		return dfs(t1, t2);
	}

private:
	bool checkSame(TreeNode *t1, TreeNode *t2) {
		if(!t1 && !t2) return 1;
		if(!t1 || !t2) return 0;
		if((t1->val == t2->val) && checkSame(t1->left, t2->left)
		    && checkSame(t1->right, t2->right)) {
			return 1;
		}
		return 0;
	}
	bool dfs(TreeNode *t1, TreeNode *t2) {
		if(!t1) return 0;
		return checkSame(t1, t2) || dfs(t1->left, t2) || dfs(t1->right, t2);
	}
};

class Solution2 {
public:
	bool checkSubTree(TreeNode *t1, TreeNode *t2) {
		if(!t2) return 1;
		vector<TreeNode *> vec;
		collect(t1, getHeigh(t2), vec);
		for(auto subt1 : vec) {
			if(equal(subt1, t2)) {
				return true;
			}
		}
		return false;
	}

private:
	unsigned getHeigh(TreeNode *root) {
		if(!root) return 0;
		return max(getHeigh(root->left), getHeigh(root->right)) + 1;
	}
	unsigned collect(TreeNode *root, unsigned h2, vector<TreeNode *> &vec) {
		if(!root) return 0;
		unsigned height = max(collect(root->left, h2, vec), collect(root->right, h2, vec)) + 1;
		if(height == h2) vec.push_back(root);
		return height;
	}
	bool equal(TreeNode *subt1, TreeNode *t2) {
		if(!subt1 && !t2) return true;
		if(!subt1 || !t2) return false;
		return (subt1->val == t2->val) && equal(subt1->left, t2->left)
		    && equal(subt1->right, t2->right);
	}
}; // 仅比较高度相等的子树，先收集这样的子树，然后对等高的进行比较

class Solution {
public:
	bool checkSubTree(TreeNode *t1, TreeNode *t2) {
		if(!t2) return 1;
		res = false, tree2 = t2;
		h2 = getHeigh(t2);
		collect(t1);
		return res;
	}

private:
	bool res;
	unsigned h2;
	TreeNode *tree2;
	unsigned getHeigh(TreeNode *root) {
		if(!root) return 0;
		return max(getHeigh(root->left), getHeigh(root->right)) + 1;
	}
	unsigned collect(TreeNode *subt1) {
		if(res || !subt1) return 0;
		unsigned height = max(collect(subt1->left), collect(subt1->right)) + 1;
		if(height == h2) res = equal(subt1, tree2);
		return height;
	}
	bool equal(TreeNode *subt1, TreeNode *subt2) {
		if(!subt1 && !subt2) return true;
		if(!subt1 || !subt2) return false;
		return (subt1->val == subt2->val) && equal(subt1->left, subt2->left)
		    && equal(subt1->right, subt2->right);
	}
}; // 不再用vector收集更高节点，而是遇到等高节点直接判断想等，然后修改全局变量res用于剪枝

int main() {
	Solution sol;
	TreeNode *t1, *t2;
	t1 = createTree({ 358,
	    361,
	    359,
	    373,
	    367,
	    360,
	    364,
	    EMPTY_NODE,
	    380,
	    368,
	    383,
	    362,
	    379,
	    EMPTY_NODE,
	    366,
	    381,
	    EMPTY_NODE,
	    385,
	    374,
	    EMPTY_NODE,
	    406,
	    363,
	    EMPTY_NODE,
	    391,
	    EMPTY_NODE,
	    372,
	    369,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    405,
	    404,
	    393,
	    397,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    375,
	    365,
	    EMPTY_NODE,
	    392,
	    403,
	    377,
	    376,
	    371,
	    EMPTY_NODE,
	    408,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    410,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    370,
	    401,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    388,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    395,
	    384,
	    382,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    411,
	    409,
	    378,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    402,
	    389,
	    EMPTY_NODE,
	    396,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    386,
	    413,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    394,
	    387,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    412,
	    399,
	    400,
	    390,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    398,
	    EMPTY_NODE,
	    407 }),
	t2 = createTree({ 363,
	    375,
	    365,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    370,
	    401,
	    409,
	    378,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    386,
	    394,
	    387,
	    412,
	    399,
	    400,
	    390,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    EMPTY_NODE,
	    398,
	    EMPTY_NODE,
	    407 });
	cout << sol.checkSubTree(t1, t2) << endl;

	t1 = createTree({ 1, 2, 3 });
	t2 = createTree({ 2 });
	cout << sol.checkSubTree(t1, t2) << endl;

	t1 = createTree({ 1, EMPTY_NODE, 2, 4 });
	t2 = createTree({ 3, 2 });
	cout << sol.checkSubTree(t1, t2) << endl;
}