// Created: 2025-12-16
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个字符串 s，请将 s 分割成一些子串，使每个子串都是 回文串，返回 s 所有可能的分割方案。
回文串是正着读和反着读都一样的字符串。
示例 1：
	输入：s = "google"
	输出：{{"g","o","o","g","l","e"},{"g","oo","g","l","e"},{"goog","l","e"}}
示例 2：
	输入：s = "aab"
	输出：{{"a","a","b"},{"aa","b"}}
示例 3：
	输入：s = "a"
	输出：{{"a"}}
提示：
	1 <= s.length <= 16
	s 仅由小写英文字母组成 */

class Solution1 {
public:
	vector<vector<string>> partition(string &s) {
		n = s.size();
		res.clear();
		begin_id = { 0 };
		begin_id.reserve(n), res.reserve(n);
		dfs(1, s);
		return std::move(res);
	}

private:
	int n;
	vector<int> begin_id;
	vector<vector<string>> res;
	// 回朔，对于元素i后的空格可以重新开始或不重新开始，对于其中是回文数的，继续回朔，然后回朔到最后一个位置，插入数组
	void dfs(int i, string &s) {
		if(i == n + 1) {
			if(begin_id.back() == n) {
				res.push_back({});
				for(unsigned i = 1; i < begin_id.size(); ++i) {
					res.back().emplace_back(s, begin_id[i - 1], begin_id[i] - begin_id[i - 1]);
				}
			}
			return;
		}
		if(check(s, begin_id.back(), i - 1)) {
			begin_id.push_back(i);
			dfs(i + 1, s);
			begin_id.pop_back();
		}
		dfs(i + 1, s);
	}
	bool check(string &s, int l, int r) {
		while(l < r) {
			if(s[l] != s[r]) return false;
			++l, --r;
		}
		return true;
	}
};

class Solution2 {
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
};

class Solution {
public:
	vector<vector<string>> partition(string &s) {
		n = s.size();
		curr.clear();
		dp.clear(); // 闭区间 i, j是否为回文子串
		dp.resize(n, vector<bool>(n, 0));
		for(int i = 0; i < n; ++i) dp[i][i] = 1;
		for(int i = n - 2; i >= 0; --i) {
			for(int j = i + 1; j < n; ++j) {
				dp[i][j] = (dp[i + 1][j - 1] && s[i] == s[j]) || (i + 1 == j && s[i] == s[j]);
			}
		}
		dfs(s, 0);
		return std::move(res);
	}

private:
	int n;
	vector<string> curr;
	vector<vector<bool>> dp;
	vector<vector<string>> res;
	void dfs(const string &s, int i) {
		if(i == n) {
			res.push_back(curr);
			return;
		}
		for(int j = i; j < n; ++j) {
			if(dp[i][j]) {
				curr.emplace_back(s, i, j - i + 1);
				dfs(s, j + 1);
				curr.pop_back();
			}
		}
	}
};

int main() {
	Solution sol;
	string s;
	s = "google";
	cout << sol.partition(s) << endl;

	s = "aab";
	cout << sol.partition(s) << endl;

	s = "a";
	cout << sol.partition(s) << endl;
}