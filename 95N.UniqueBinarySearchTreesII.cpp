// Created: 2025-06-06
#include "MyTreeNode.h"
#include "MyUtils.hpp"

/* 95. 不同的二叉搜索树 II
给你一个整数 n，请你生成并返回所有由 n 个节点组成且节点值从 1 到 n 互不相同的不同 二叉搜索树。
可以按 任意顺序 返回答案。
示例 1：
	输入：n = 3
	输出：{{1,null,2,null,3},{1,null,3,2},{2,1,3},{3,1,null,null,2},{3,2,null,1}}
示例 2：
	输入：n = 1
	输出：{{1}}
提示：
	1 <= n <= 8 */

class Solution1 {
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
		memo.clear();
		return std::move(dfs(1, n)); // 成员变量不会进行返回值优化，需要move
	}

private:
	struct HashPair {
		size_t operator()(const pair<int, int> &pa) const {
			return (size_t)pa.first << 32 | (size_t)pa.second;
		}
	};
	unordered_map<pair<int, int>, vector<TreeNode *>, HashPair> memo;
	vector<TreeNode *> &dfs(int l, int r) {
		vector<TreeNode *> &res = memo[{ l, r }];
		if(!res.empty()) return res;
		vector<TreeNode *> nullvec { nullptr }; // 递归终点
		res.reserve(size[r - l + 1]);
		for(int i = l; i <= r; ++i) {
			vector<TreeNode *> &lvec = l <= i - 1 ? dfs(l, i - 1) : nullvec;
			vector<TreeNode *> &rvec = i + 1 <= r ? dfs(i + 1, r) : nullvec;
			for(auto l : lvec) {
				for(auto r : rvec) {
					res.push_back(new TreeNode(i));
					res.back()->left = l;
					res.back()->right = r;
				}
			}
		}
		return res;
	}
	inline static constexpr array<int, 20> size = []() {
		array<int, 20> dp {};
		dp[0] = 1, dp[1] = 1;
		for(int i = 2; i < 20; ++i) {
			for(int j = 0; j < i; ++j) {
				dp[i] += dp[j] * dp[i - j - 1];
			}
		}
		return dp;
	}();
};

int main() {
	Solution sol;
}