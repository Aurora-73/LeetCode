// Created: 2025-06-06
#include "MyUtils.hpp"

/* 95. 不同的二叉搜索树 II
给你一个整数 n，请你生成并返回所有由 n 个节点组成且节点值
从 1 到 n 互不相同的不同 二叉搜索树。可以按 任意顺序 返回答案。*/

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) { }
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) { }
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) { }
};

class Solution {
public:
	vector<TreeNode *> generateTrees(int n) {
		vector<vector<TreeNode *>> dp(n + 1);
		dp[0] = { nullptr };
		dp[1] = { new TreeNode(1) };
		for(int i = 2; i <= n; ++i) {
			for(int j = 0; j < i; ++j) {
				auto &leftVec = dp[j], &rightVec = dp[i - j - 1];
				for(auto left : leftVec) {
					for(auto right : rightVec) {
						dp[i].push_back(
						    new TreeNode(j + 1, buildAs(left, 0), buildAs(right, j + 1)));
					}
				}
			}
		}
		for(int i = 0; i < n; ++i) {
			for(auto &root : dp[i]) {
				PostOrderDelete(root);
			}
		} // 解决内存泄漏问题
		return std::move(dp.back()); // 用不了返回值优化，直接移动语义
	}

private:
	TreeNode *buildAs(TreeNode *refer, int offset) {
		if(!refer) return nullptr;
		return new TreeNode(
		    refer->val + offset, buildAs(refer->left, offset), buildAs(refer->right, offset));
	}

	void PostOrderDelete(TreeNode *root) {
		if(!root) {
			return;
		}
		PostOrderDelete(root->left);
		PostOrderDelete(root->right);
		delete root;
	}
};

class Solution {
public:
	vector<TreeNode *> generateTrees(int n) {
		return dfs(1, n + 1);
	}

private:
	vector<TreeNode *> null = { nullptr };
	unordered_map<int, vector<TreeNode *>> memo;
	vector<TreeNode *> &dfs(int l, int r) {
		if(l >= r) return null;
		int key = l + r * 10; // l r 都在 0 - 9, 或者使用二元组哈希的方法也行
		auto [it, inserted] = memo.insert({ key, {} });
		if(inserted) {
			for(int i = l; i < r; ++i) {
				const auto &leftVec = dfs(l, i);
				const auto &rightVec = dfs(i + 1, r);
				for(auto &left : leftVec) {
					for(auto &right : rightVec) {
						it->second.push_back(new TreeNode(i, left, right));
					}
				}
			}
		}
		return it->second;
	}
};

int main() {
	Solution sol;
}