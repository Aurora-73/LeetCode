// Created: 2025-12-18
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定两个字符串text1 和text2，返回这两个字符串的最长 公共子序列 的长度。
如果不存在 公共子序列，返回 0。
一个字符串的子序列是指这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。

	例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。
示例 1：
	输入：text1 = "abcde", text2 = "ace" 
	输出：3  
	解释：最长公共子序列是 "ace"，它的长度为 3。
示例 2：
	输入：text1 = "abc", text2 = "abc"
	输出：3
	解释：最长公共子序列是 "abc"，它的长度为 3。
示例 3：
	输入：text1 = "abc", text2 = "def"
	输出：0
	解释：两个字符串没有公共子序列，返回 0。
提示：
	1 <= text1.length, text2.length <= 1000
	text1 和text2 仅由小写英文字符组成。 */

class Solution1 {
public:
	int longestCommonSubsequence(string &text1, string &text2) {
		int n1 = text1.size(), n2 = text2.size();
		vector<vector<int>> dp(n1 + 1, vector<int>(n2 + 1));
		for(int i = 1; i < n1 + 1; ++i) {
			for(int j = 1; j < n2 + 1; ++j) {
				if(text1[i - 1] == text2[j - 1])
					dp[i][j] = dp[i - 1][j - 1] + 1;
				else
					dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
			}
		}
		return dp.back().back();
	}
}; // if(text1[..] == text2[..]) dp[i][j] = dp[i - 1][j - 1] + 1;
// else dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
// 如果这连两个位置相等，贪心地匹配这两个位置不考虑这两个的后缀，否则不考虑某一个的后缀求最大

class Solution2 {
public:
	int longestCommonSubsequence(string &text1, string &text2) {
		int n1 = text1.size(), n2 = text2.size();
		vector<int> curr(n2 + 1), next(n2 + 1);
		for(int i = 1; i < n1 + 1; ++i) {
			for(int j = 1; j < n2 + 1; ++j) {
				if(text1[i - 1] == text2[j - 1])
					next[j] = curr[j - 1] + 1;
				else
					next[j] = max(next[j - 1], curr[j]);
			}
			swap(next, curr);
		}
		return curr.back();
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
}; // 只有对角线的值会被覆盖，对角线使用一个单独的数保存

int main() {
	Solution sol;
	string text1, text2;
	text1 = "abcde", text2 = "ace";
	cout << sol.longestCommonSubsequence(text1, text2) << endl;
	text1 = "abc", text2 = "abc";
	cout << sol.longestCommonSubsequence(text1, text2) << endl;
	text1 = "abc", text2 = "def";
	cout << sol.longestCommonSubsequence(text1, text2) << endl;
}