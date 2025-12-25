// Created: 2025-12-25
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个有序整数数组，元素各不相同且按升序排列，编写一个算法，创建一棵高度最小的二叉搜索树。
示例：
给定有序数组: {-10,-3,0,5,9},
一个可能的答案是：{0,-3,9,-10,null,5}，它可以表示下面这个高度平衡二叉搜索树：
          0 
         / \ 
       -3   9 
       /   / 
     -10  5  */

class Solution1 {
public:
	TreeNode *sortedArrayToBST(vector<int> &nums) {
		root = nullptr;
		int l = 0, r = nums.size();
		todo(nums, l, r);
		return root;
	}

private:
	TreeNode *root;
	void todo(vector<int> &nums, int l, int r) {
		if(l >= r) return;
		int mid = (r - l) / 2 + l;
		insert(nums[mid], root);
		todo(nums, mid + 1, r);
		todo(nums, l, mid);
	}
	void insert(int val, TreeNode *&root) {
		if(!root) {
			root = new TreeNode(val);
			return;
		}
		if(root->val > val) {
			insert(val, root->left);
		} else {
			insert(val, root->right);
		}
	}
}; // 每次插入子串中最靠近中间的值

class Solution {
public:
	TreeNode *sortedArrayToBST(vector<int> &nums) {
		return build(nums, 0, nums.size());
	}

private:
	TreeNode *build(const vector<int> &nums, int l, int r) {
		if(l >= r) return nullptr;
		int mid = l + (r - l) / 2;
		TreeNode *root = new TreeNode(nums[mid]);
		root->left = build(nums, l, mid);
		root->right = build(nums, mid + 1, r);
		return root;
	}
}; // 更好的方法：直接构造，而不是插入

int main() {
	Solution sol;
	vector<int> nums;
	nums = { -10, -3, 0, 5, 9 };
	cout << sol.sortedArrayToBST(nums) << endl;
}