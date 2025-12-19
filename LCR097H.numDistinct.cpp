// Created: 2025-12-19
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个字符串 s 和一个字符串 t，计算在 s 的子序列中 t 出现的个数。
字符串的一个 子序列 是指，通过删除一些（也可以不删除）字符且不干扰剩余字符相对位置所组成的新字符串。
（例如，"ACE" 是 "ABCDE" 的一个子序列，而 "AEC" 不是）
题目数据保证答案符合 32 位带符号整数范围。
示例 1：
	输入：s = "rabbbit", t = "rabbit"
	输出：3
示例 2：
	输入：s = "babgbag", t = "bag"
	输出：5
提示：
	0 <= s.length, t.length <= 1000
	s 和 t 由英文字母组成
注意：本题与主站 115 题相同：  */

class Solution1 {
public:
	int numDistinct(string &s, string &t) {
		ns = s.size(), nt = t.size();
		return dfs(s, t, 0, 0);
	}

private:
	int ns, nt;
	int dfs(string &s, string &t, int i, int j) {
		if(j == nt) return 1;
		if(i == ns) return 0;
		if(s[i] == t[j]) {
			return dfs(s, t, i + 1, j + 1) + dfs(s, t, i + 1, j);
		} else {
			return dfs(s, t, i + 1, j);
		}
	}
}; // dfs(i, j)： s的后i个字符与t的后j个字符的出现数

class Solution2 {
public:
	int numDistinct(string &s, string &t) {
		int ns = s.size(), nt = t.size();
		vector<vector<int>> dp(ns + 1, vector<int>(nt + 1));
		for(int i = 0; i < ns + 1; ++i) dp[i].back() = 1;
		for(int i = ns - 1; i >= 0; --i) {     // 必须单向
			for(int j = nt - 1; j >= 0; --j) { // 双向皆可
				if(s[i] == t[j]) {
					dp[i][j] = min(dp[i + 1][j + 1], INT_MAX - dp[i + 1][j]) + dp[i + 1][j];
				} else {
					dp[i][j] = dp[i + 1][j];
				}
			}
		}
		return dp.front().front();
	}
};

class Solution {
public:
	int numDistinct(string &s, string &t) {
		int ns = s.size(), nt = t.size();
		vector<int> dp(nt + 1);
		dp.back() = 1;
		for(int i = ns - 1; i >= 0; --i) {
			for(int j = 0; j < nt; ++j) { // 双向皆可 + 防覆盖 = 必须单向
				if(s[i] == t[j]) {
					dp[j] += min(dp[j + 1], INT_MAX - dp[j]);
				}
			}
		}
		return dp.front();
	}
};

int main() {
	Solution sol;
	string s, t;
	s = "rabbbit", t = "rabbit";
	cout << sol.numDistinct(s, t) << endl; // 3
	s = "babgbag", t = "bag";
	cout << sol.numDistinct(s, t) << endl; // 5
}