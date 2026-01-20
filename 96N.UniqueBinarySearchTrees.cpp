// Created: 2025-06-06
#include "MyUtils.hpp"

/*96. 不同的二叉搜索树
给你一个整数 n ，求恰由 n 个节点组成且节点值从 1 到 n 互不相同的 二叉搜索树 有多少种？返回满足题意的二叉搜索树的种数。
示例 1：
    输入：n = 3
    输出：5
示例 2：
    输入：n = 1
    输出：1
提示：
    1 <= n <= 19 */

class Solution1 {
public:
	int numTrees(int n) {
		vector<int> dp(n + 1);
		dp[0] = 1, dp[1] = 1;
		for(int i = 2; i <= n; ++i) {
			for(int j = 0; j < i; ++j) {
				dp[i] += dp[j] * dp[i - j - 1];
			}
		}
		return dp.back();
	}
};

class Solution2 {
public:
	int numTrees(int n) {
		long long C = 1;
		for(int i = 0; i < n; ++i) {
			C = C * 2 * (2 * i + 1) / (i + 2);
		}
		return (int)C;
	}
}; // 卡塔兰数 C

class Solution {
public:
	int numTrees(int n) {
		return results[n];
	}

private:
	static constexpr int size = 20;
	inline static constexpr array<int, size> results = []() {
		array<int, size> dp {};
		dp[0] = 1, dp[1] = 1;
		for(int i = 2; i < size; ++i) {
			for(int j = 0; j < i; ++j) {
				dp[i] += dp[j] * dp[i - j - 1];
			}
		}
		return dp;
	}();
};

int main() {
	Solution sol;
	Solution1 sol1;
	Solution2 sol2;
	for(int i = 1; i < 20; ++i) {
		cout << sol.numTrees(i) << ", " << sol1.numTrees(i) << ", " << sol2.numTrees(i) << '\n';
	}
}