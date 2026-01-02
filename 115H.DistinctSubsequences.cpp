// Created: 2025-06-03
#include "MyUtils.hpp"

/*115. 不同的子序列
给你两个字符串 s 和 t ，统计并返回在 s 的 子序列 中 t 出现的个数。
测试用例保证结果在 32 位有符号整数范围内。*/

class Solution1 {
public:
	int numDistinct(const string &s, const string &t) {
		m = s.size();
		n = t.size();
		// 把 memo[i][j] 初始化为 -1，表示“s[i:] 匹配 t[j:] 的子问题还没算过”
		memo.assign(m, vector<int>(n, -1));
		return dfs(s, t, 0, 0);
	}

private:
	int m, n;
	// memo[i][j] = numDistinct(s[i:], t[j:])
	vector<vector<int>> memo;

	int dfs(const string &s, const string &t, int i, int j) {
		// 如果 t 已经全匹配完了，剩下 s[i:] 都算是一种匹配方式
		if(j == n) {
			return 1;
		}
		// 如果 s 到头了（i == m）或剩余长度不够匹配（m-i < n-j），直接返回 0
		if(i == m || m - i < n - j) {
			return 0;
		}
		// 如果先前算过，就直接返回
		if(memo[i][j] != -1) {
			return memo[i][j];
		}
		int ans = 0;
		// 如果 s[i] == t[j]：可以选择“匹配这对字符”或“跳过 s[i]”
		if(s[i] == t[j]) {
			// 1. 匹配 s[i] 与 t[j]，于是去算 dfs(i+1, j+1)
			// 2. 跳过 s[i]，于是去算 dfs(i+1, j)
			ans = dfs(s, t, i + 1, j + 1) + dfs(s, t, i + 1, j);
		} else {
			// 如果 s[i] != t[j]，只能跳过 s[i]，去算 dfs(i+1, j)
			ans = dfs(s, t, i + 1, j);
		}

		return memo[i][j] = ans;
	}
}; // 选或不选的思想，相等时可选可不选，不相等时只能不选

class Solution2 {
public:
	int numDistinct(const string &s, const string &t) {
		int m = s.size(), n = t.size();
		// dp[i][j] 表示 s[i:] 中 t[j:] 出现的个数
		vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

		// 初始化：当 t[j:] 是空字符串时，无论 s[i:] 是什么，都有 1 个匹配
		for(int i = 0; i <= m; ++i) {
			dp[i][n] = 1;
		}
		// 倒序填表
		for(int i = m - 1; i >= 0; --i) {
			for(int j = n - 1; j >= 0; --j) {
				if(s[i] == t[j]) {
					if(numeric_limits<int>::max() - dp[i + 1][j + 1] < dp[i + 1][j]) {
						dp[i][j] = numeric_limits<int>::max();
					} else {
						dp[i][j] = dp[i + 1][j + 1] + dp[i + 1][j];
					}
				} else {
					dp[i][j] = dp[i + 1][j];
				}
			}
		}
		for(int i = m; i >= 0; --i) {
			cout << dp[i] << endl;
		}
		return dp[0][0];
	}
};

class Solution {
public:
	int numDistinct(const string &s, const string &t) {
		int m = s.size(), n = t.size();
		vector<int> dp(n, 0);
		for(int i = m - 1; i >= 0; --i) {
			int pre = 1;
			for(int j = n - 1; j >= 0; --j) {
				int temp = dp[j];
				if(s[i] == t[j]) {
					if(numeric_limits<int>::max() - pre < dp[j]) {
						dp[j] = numeric_limits<int>::max();
					} else {
						dp[j] = pre + dp[j];
					}
				} else {
					dp[j] = dp[j];
				}
				pre = temp;
			}
		}
		return dp[0];
	}
};

int main() {
	Solution sol;
	Solution2 sol2;
	cout << sol.numDistinct("babgbag", "bag") << endl;
	cout << sol2.numDistinct("babgbag", "bag") << endl;
}