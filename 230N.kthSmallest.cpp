// Created: 2025-05-04
#include "MyUtils.h"
#include "MyTreeNode.h"

/*230. 二叉搜索树中第 K 小的元素
给定一个二叉搜索树的根节点 root ，和一个整数 k ，请你设计一个算法查找其中第 k 小的元素（从 1 开始计数）。*/

class Solution1 {
public:
	int kthSmallest(TreeNode *root, int &k) {
		if(!root)
			return -1;
		int l = kthSmallest(root->left, k);
		if(l != -1) {
			return l;
		}
		k--;
		if(k == 0)
			return root->val;
		int r = kthSmallest(root->right, k);
		if(r != -1) {
			return r;
		}
		return -1;
	}
}; // 需要用引用

class Solution2 {
public:
	int kthSmallest(TreeNode *root, int &k) {
		if(kkk == -1)
			kkk = k;
		if(!root)
			return -1;
		int l = kthSmallest(root->left, kkk);
		if(l != -1) {
			return l;
		}
		kkk--;
		if(kkk == 0) {
			kkk = -1; // 不用担心每次调用都会检测kkk是否为-1，如果是则会重置kkk 所以这里重置不了
			// 如果返回了非 -1 值会直接一路return，所以不会被检测
			return root->val;
		}
		int r = kthSmallest(root->right, kkk);
		if(r != -1) {
			return r;
		}
		return -1;
	}

private:
	int kkk = -1;
}; // 不用引用而是用成员变量

class Solution {
public:
	int kthSmallest(TreeNode *root, int k) {
		return dfs(root, k);
	}

private:
	int dfs(TreeNode *root, int &k) {
		if(!root)
			return -1;
		int l = dfs(root->left, k);
		if(l != -1)
			return l;
		if(--k == 0)
			return root->val;
		return dfs(root->right, k);
	}
}; // 还是直接调用比较好

int main() {
	Solution1 sol1;
}