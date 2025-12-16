// Created: 2025-06-14
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 131. 分割回文串
给你一个字符串 s，请你将 s 分割成一些 子串，使每个子串都是 回文串。
返回 s 所有可能的分割方案。
示例 1：
	输入：s = "aab"
	输出：{{"a","a","b"},{"aa","b"}}
示例 2：
	输入：s = "a"
	输出：{{"a"}}
提示：
	1 <= s.length <= 16
	s 仅由小写英文字母组成 */

class Solution1 {
public:
	vector<vector<string>> partition(string &s) {
		res.clear();
		n = s.size();
		now.reserve(n), res.reserve(n);
		dfs(s, 0, 0);
		return res;
	}

private:
	int n;
	vector<string> now;
	vector<vector<string>> res;
	void dfs(string &s, int i, int j) {
		if(j >= n) {
			if(isPalindrome(s, i, j)) {
				res.push_back(now);
			}
			return;
		}
		if(isPalindrome(s, i, j)) {
			now.emplace_back(s, i, j - i + 1);
			dfs(s, j + 1, j + 1);
			now.pop_back();
		}
		dfs(s, i, j + 1);
	}
	bool isPalindrome(string &s, int i, int j) {
		while(i < j) {
			if(s[i] != s[j]) {
				return false;
			}
			++i, --j;
		}
		return true;
	}
}; // 回朔，如果当前是回文数，则分为切开和不切开两种情况

class Solution {
public:
	vector<vector<string>> partition(string &s) {
		int n = s.size();
		// 预处理回文子串
		vector<vector<bool>> dp(n, vector<bool>(n, false));
		for(int i = n - 1; i >= 0; --i) {
			for(int j = i; j < n; ++j) {
				dp[i][j] = (s[i] == s[j]) && (j - i < 2 || dp[i + 1][j - 1]);
			}
		}
		vector<string> path;
		vector<vector<string>> res;
		dfs(s, 0, dp, path, res);
		return res;
	}

private:
	void dfs(const string &s,
	    int start,
	    const vector<vector<bool>> &dp,
	    vector<string> &path,
	    vector<vector<string>> &res) {
		int n = s.size();
		if(start == n) {
			res.push_back(path);
			return;
		}
		for(int end = start; end < n; ++end) {
			if(dp[start][end]) {
				path.emplace_back(s, start, end - start + 1);
				// string 有和 substr 相同参数的构造函数
				dfs(s, end + 1, dp, path, res);
				path.pop_back();
			}
		}
	}
}; // 动态规划先判断是否为回文数，然后回朔会快很多

int main() {
	Solution sol;
	string s;
	s = "aab";
	cout << sol.partition(s) << endl;
	s = "a";
	cout << sol.partition(s) << endl;
}