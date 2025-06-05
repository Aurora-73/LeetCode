// Created: 2025-06-05
#include "MyUtils.h"

/* 1143. 最长公共子序列
给定两个字符串 text1 和 text2，返回这两个字符串的最长 公共子序列 的长度。如果不存在 公共子序列 ，返回 0 。
一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。*/

class Solution1 {
public:
	int longestCommonSubsequence(string &text1, string &text2) {
		int res, n1 = text1.size(), n2 = text2.size();
		vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1));
		for(int i = n1 - 1; i >= 0; --i) {
			for(int j = n2 - 1; j >= 0; --j) {
				if(text1[i] == text2[j]) {
					dp[i][j] = dp[i + 1][j + 1] + 1;
				} else {
					dp[i][j] = max(dp[i][j + 1], dp[i + 1][j]);
				}
			}
		}
		return dp[0][0];
	}
};

class Solution2 {
public:
	int longestCommonSubsequence(string &text1, string &text2) {
		int res, n1 = text1.size(), n2 = text2.size();
		vector<int> curr(n2 + 1), prev(n2 + 1);
		for(int i = n1 - 1; i >= 0; --i) {
			swap(curr, prev);
			for(int j = n2 - 1; j >= 0; --j) {
				if(text1[i] == text2[j]) {
					curr[j] = prev[j + 1] + 1;
				} else {
					curr[j] = max(curr[j + 1], prev[j]);
				}
			}
		}
		return curr[0];
	}
};

class Solution {
public:
	int longestCommonSubsequence(string &text1, string &text2) {
		int n1 = text1.size(), n2 = text2.size();
		vector<int> dp(n2 + 1);
		for(int i = n1 - 1; i >= 0; --i) {
			int diag = 0; // 等价于 prev[j + 1]
			for(int j = n2 - 1; j >= 0; --j) {
				int tmp = dp[j]; // 保存 dp[j] 原值，作为下次循环的 diag
				if(text1[i] == text2[j]) {
					dp[j] = diag + 1;
				} else {
					dp[j] = max(dp[j + 1], dp[j]);
				}
				diag = tmp;
			}
		}
		return dp[0];
	}
};

int main() {
	Solution sol;
}