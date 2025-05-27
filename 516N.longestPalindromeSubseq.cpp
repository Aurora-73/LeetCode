// Created: 2025-05-27
#include "MyUtils.h"

/* 516. 最长回文子序列
给你一个字符串 s ，找出其中最长的回文子序列，并返回该序列的长度。
子序列定义为：不改变剩余字符顺序的情况下，删除某些字符或者不删除任何字符形成的一个序列。*/

class Solution1 {
public:
	int longestPalindromeSubseq(const string &s) {
		n = s.size();
		memo.resize(n, vector<int>(n, INT_MAX));
		return dfs(s, 0, n - 1);
	}

private:
	int n;
	vector<vector<int>> memo;
	int dfs(const string &s, int begin, int end) {
		if(begin > end) return 0;
		if(begin == end) return 1;
		if(memo[begin][end] != INT_MAX) return memo[begin][end];
		if(s[begin] == s[end]) {
			memo[begin][end] = dfs(s, begin + 1, end - 1) + 2;
		} else {
			memo[begin][end] = max(dfs(s, begin + 1, end), dfs(s, begin, end - 1));
		}
		return memo[begin][end];
	}
};

class Solution2 {
public:
	int longestPalindromeSubseq(const string &s) {
		int n = s.size();
		vector<vector<int>> dp(n, vector<int>(n, 0));
		for(int i = 0; i < n; ++i) {
			dp[i][i] = 1;
		}
		for(int i = n - 2; i >= 0; --i) {
			for(int j = i + 1; j < n; ++j) {
				if(s[i] == s[j]) {
					dp[i][j] = dp[i + 1][j - 1] + 2;
				} else {
					dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
				}
			}
		}
		return dp[0][n - 1];
	}
};

class Solution {
public:
	int longestPalindromeSubseq(const string &s) {
		int n = s.size();
		vector<int> curr(n), prev(n);
		prev.back() = 1;
		for(int i = n - 2; i >= 0; --i) {
			curr[i] = 1;
			for(int j = i + 1; j < n; ++j) {
				if(s[i] == s[j]) {
					curr[j] = prev[j - 1] + 2;
				} else {
					curr[j] = max(prev[j], curr[j - 1]);
				}
			}
			std::swap(prev, curr);
		}
		return prev[n - 1];
	}
}; // 通过交换和重置必要位来进行数组优化
/*
[1,↙,↙,↙,↙ ]
[0,1 ,↙,↙,↙ ]
[0,0 ,1 ,↙,↙]
[0,0 ,0 ,1 ,↙]
[0,0 ,0 ,0 ,1 ]
每次滚动只用把主对角线置为 1 即可，其他的非 0 元素都会被覆盖，0 都可以用
*/

int main() {
	Solution sol;
	cout << sol.longestPalindromeSubseq("bbbab");
	// cout << sol.longestPalindromeSubseq(
	//     "fwdfawbdwafawbdiawdagurhgbrsuyfcatrdawtdwtydgacwghccabeuafbjkfhadfiawdwaifjhsugrvaskvjefij"
	//     "aiofgharegoaewjfwfsnbvusjvseiosbvshniosefweiofnafioawnbuirsgveroihgweifgpga");
}