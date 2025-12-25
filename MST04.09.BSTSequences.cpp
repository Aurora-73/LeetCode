// Created: 2025-12-25
#include "MyTreeNode.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 从左向右遍历一个数组，通过不断将其中的元素插入树中可以逐步地生成一棵二叉搜索树。
给定一个由不同节点组成的二叉搜索树 root，输出所有可能生成此树的数组。
示例 1：
	输入：root = {2,1,3}
	输出：{{2,1,3},{2,3,1}}
	解释：数组 {2,1,3}、{2,3,1} 均可以通过从左向右遍历元素插入树中形成以下二叉搜索树
	      2 
	     / \ 
	    1   3
示例2：
	输入：root = {4,1,null,null,3,2}
	输出：{{4,1,3,2}}
提示：
	二叉搜索树中的节点数在{0, 1000}的范围内
	1 <= 节点值<= 10^6
	用例保证符合要求的数组数量不超过 5000 */

class Solution1 {
public:
	vector<vector<int>> BSTSequences(TreeNode *root) {
		if(!root) return { {} };
		vector<vector<int>> lres = BSTSequences(root->left), rres = BSTSequences(root->right);
		vector<vector<int>> res;
		curr = { root->val };
		// 先把root->val插入进curr中，保证res的每个都会以root->val开头，且清空之前产生的curr值
		for(auto &lr : lres) {
			for(auto &rr : rres) {
				weave(lr, rr, 0, 0, res);
			}
		}
		return res;
	}

private:
	vector<int> curr;
	void weave(vector<int> &vec1, vector<int> &vec2, int i, int j, vector<vector<int>> &res) {
		if(i == vec1.size() && j == vec2.size()) {
			res.push_back(curr);
			return;
		}
		if(i < vec1.size()) {
			curr.push_back(vec1[i]);
			weave(vec1, vec2, i + 1, j, res);
			curr.pop_back();
		}
		if(j < vec2.size()) {
			curr.push_back(vec2[j]);
			weave(vec1, vec2, i, j + 1, res);
			curr.pop_back();
		}
	}
}; /* 分治 + 交织
   首先假设左右子树的全部可能解已知，为lres和rres，求解当前根节点的可能情况：
   首先根节点必须位于每个序列的顶端，且lres和rres内部的元素的顺序不可打乱
   因此直接采用全排列类似的回朔解法求解，注意求解的时候要先把root->val放到curr中，
   这样由于这个值在回朔过程中不会被pop，就可以实现根节点在最前端  */

class Solution {
public:
	vector<vector<int>> BSTSequences(TreeNode *root) {
		if(!root) return { {} };
		path.clear();
		deque<TreeNode *> candidates;
		candidates.push_back(root);
		dfs(candidates);
		return std::move(res);
	}

private:
	vector<vector<int>> res;
	vector<int> path;
	void dfs(deque<TreeNode *> &candidates) {
		if(candidates.empty()) {
			res.push_back(path);
			return;
		}
		int size = candidates.size();
		for(int i = 0; i < size; ++i) {
			TreeNode *curr = candidates.front();
			candidates.pop_front();
			path.push_back(curr->val);
			if(curr->left) candidates.push_back(curr->left);
			if(curr->right) candidates.push_back(curr->right);
			dfs(candidates);
			if(curr->left) candidates.pop_back();
			if(curr->right) candidates.pop_back();
			path.pop_back();
			candidates.push_back(curr);
		} // deque旋转，每次只处理队首的元素，从而避免插入和删除正在访问的元素。
	}
}; // 直接回朔解法，注意deque及其旋转

int main() {
	Solution sol;
	TreeNode *root;
	root = createTree({ 2, 1, 3 });
	cout << sol.BSTSequences(root) << endl;

	root = createTree({ 4, 1, EMPTY_NODE, EMPTY_NODE, 3, 2 });
	cout << sol.BSTSequences(root) << endl;
}