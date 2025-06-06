// Created: 2025-05-28
#include "MyUtils.hpp"

/*712. 两个字符串的最小ASCII删除和
给定两个字符串s1 和 s2，返回 使两个字符串相等所需删除字符的 ASCII 值的最小和 。*/

class Solution1 {
public:
	int minimumDeleteSum(const string &s1, const string &s2) {
		n1 = s1.size(), n2 = s2.size();
		memo.resize(n1, vector<int>(n2, -1));
		int min_val = INT_MAX;
		min_val = min(dfs(s1, s2, 0, 0), min_val);
		cout << memo << endl;
		return min_val;
	}

private:
	int n1, n2;
	vector<vector<int>> memo;
	int dfs(const string &s1, const string &s2, int i, int j) {
		if(i >= n1 || j >= n2) {
			int sum = 0;
			while(i < n1) sum += s1[i++];
			while(j < n2) sum += s2[j++];
			return sum;
		}
		if(memo[i][j] == -1) {
			if(s1[i] == s2[j]) {
				memo[i][j] = dfs(s1, s2, i + 1, j + 1);
			} else {
				memo[i][j] = min(dfs(s1, s2, i + 1, j) + s1[i], dfs(s1, s2, i, j + 1) + s2[j]);
			}
		}
		return memo[i][j];
	}
};

class Solution2 {
public:
	int minimumDeleteSum(const string &s1, const string &s2) {
		int n1 = s1.size(), n2 = s2.size();
		vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1, 0));
		for(int j = n2 - 1; j >= 0; --j) {
			dp[n1][j] = dp[n1][j + 1] + s2[j];
		}
		for(int i = n1 - 1; i >= 0; --i) {
			dp[i][n2] = dp[i + 1][n2] + s1[i];
		}
		for(int i = n1 - 1; i >= 0; --i) {
			for(int j = n2 - 1; j >= 0; --j) {
				if(s1[i] == s2[j]) {
					dp[i][j] = dp[i + 1][j + 1];
				} else {
					dp[i][j] = min(dp[i + 1][j] + s1[i], dp[i][j + 1] + s2[j]);
				}
			}
		}
		cout << dp << endl;
		return dp[0][0];
	}
};

class Solution3 {
public:
	int minimumDeleteSum(const string &s1, const string &s2) {
		int n1 = s1.size(), n2 = s2.size();
		vector<int> curr(n2 + 1), prev(n2 + 1);
		for(int j = n2 - 1; j >= 0; --j) {
			curr[j] = curr[j + 1] + s2[j];
		}
		for(int i = n1 - 1; i >= 0; --i) {
			std::swap(prev, curr);
			curr[n2] = prev[n2] + s1[i];
			for(int j = n2 - 1; j >= 0; --j) {
				if(s1[i] == s2[j]) {
					curr[j] = prev[j + 1];
				} else {
					curr[j] = min(prev[j] + s1[i], curr[j + 1] + s2[j]);
				}
			}
		}
		return curr[0];
	}
};

class Solution {
public:
	int minimumDeleteSum(const string &s1, const string &s2) {
		if(s1.size() > s2.size()) {
			return helper(s2, s1);
		} else {
			return helper(s1, s2);
		}
	}

private:
	int helper(const string &s, const string &t) {
		int n = s.size(), m = t.size();
		vector<int> curr(m + 1), prev(m + 1);

		// 初始化curr数组
		for(int j = m - 1; j >= 0; --j) {
			curr[j] = curr[j + 1] + t[j];
		}

		for(int i = n - 1; i >= 0; --i) {
			swap(prev, curr);
			curr[m] = prev[m] + s[i];
			for(int j = m - 1; j >= 0; --j) {
				if(s[i] == t[j]) {
					curr[j] = prev[j + 1];
				} else {
					curr[j] = min(prev[j] + s[i], curr[j + 1] + t[j]);
				}
			}
		}
		return curr[0];
	}
}; // 短数组优化

int main() {
	Solution sol;
	Solution2 sol2;
	// cout << sol.minimumDeleteSum("delete", "leet") << endl;
	// cout << sol2.minimumDeleteSum("delete", "leet") << endl;
	cout << sol.minimumDeleteSum("ccaccjp", "fwosarcwge") << endl;
	cout << sol2.minimumDeleteSum("ccaccjp", "fwosarcwge") << endl;
}