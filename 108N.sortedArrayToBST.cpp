// Created: 2025-05-09
#include "MyTreeNode.h"
#include "MyUtils.hpp"

/*108. 将有序数组转换为二叉搜索树

给你一个整数数组 nums ，其中元素已经按 升序 排列，请你将其转换为一棵 平衡 二叉搜索树。*/

class Solution1 {
public:
	TreeNode *sortedArrayToBST(vector<int> &nums) {
		return iteratorToBST(nums.begin(), nums.end());
	}
	TreeNode *iteratorToBST(vector<int>::iterator begin, vector<int>::iterator end) {
		if(begin >= end) return nullptr;
		auto middle = begin + (end - begin) / 2;
		TreeNode *root = new TreeNode(*middle);
		root->left = iteratorToBST(begin, middle);
		root->right = iteratorToBST(middle + 1, end);
		return root;
	}
};

class Solution2 {
public:
	TreeNode *sortedArrayToBST(const vector<int> &nums) {
		if(nums.empty()) return nullptr;
		int lo = 0, hi = nums.size() - 1;
		int mid = lo + (hi - lo) / 2;
		TreeNode *root = new TreeNode(nums[mid]);
		struct Frame {
			int lo, hi;
			TreeNode **link;
		};
		stack<Frame> st;
		// 先右后左，保证出栈时先处理左子树
		st.push({ mid + 1, hi, &root->right });
		st.push({ lo, mid - 1, &root->left });
		while(!st.empty()) {
			auto [l, h, link] = st.top();
			st.pop();
			if(l > h) continue;
			int m = l + (h - l) / 2;
			*link = new TreeNode(nums[m]);
			// 子任务：右、左
			st.push({ m + 1, h, &((*link)->right) });
			st.push({ l, m - 1, &((*link)->left) });
		}
		return root;
	}
};

int main() {
	Solution1 sol1;
}