// Created: 2025-12-19
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个字符串 s，请将 s 分割成一些子串，使每个子串都是回文串。
返回符合要求的 最少分割次数。
示例 1：
	输入：s = "aab"
	输出：1
	解释：只需一次分割就可将s 分割成 {"aa","b"} 这样两个回文子串。
示例 2：
	输入：s = "a"
	输出：0
示例 3：
	输入：s = "ab"
	输出：1
提示：
	1 <= s.length <= 2000
	s 仅由小写英文字母组成 */

class Solution1 {
public:
	int minCut(string &s) {
		n = s.size();
		dp = vector<vector<bool>>(n, vector<bool>(n));
		for(int i = 0; i < n; ++i) dp[i][i] = 1;
		for(int i = n - 1; i >= 0; --i) {
			for(int j = i + 1; j < n; ++j) {
				dp[i][j] = (s[i] == s[j]) && (i + 1 > j - 1 || dp[i + 1][j - 1]);
			}
		}
		return dfs(s, 0) - 1; // 要减去最初有一个串，a次切割会分为a + 1个子串
	}

private:
	int n;
	vector<vector<bool>> dp;
	int dfs(string &s, int i) {
		if(i >= n) return 0;
		int temp = INT_MAX;
		for(int j = i; j < n; ++j) {
			if(dp[i][j]) temp = min(temp, dfs(s, j + 1));
		}
		return temp + 1;
	} // 从 i 开始的子串的最少分割次数
}; // dp[i][j]：闭区间[i, j]是否是回文子串

class Solution2 {
public:
	int minCut(string &s) {
		int n = s.size();
		vector<vector<bool>> ispal(n, vector<bool>(n));
		for(int i = 0; i < n; ++i) ispal[i][i] = 1;
		for(int i = n - 1; i >= 0; --i) {
			for(int j = i + 1; j < n; ++j) {
				ispal[i][j] = (s[i] == s[j]) && (i + 1 > j - 1 || ispal[i + 1][j - 1]);
			}
		} // ispal[i][j]：闭区间[i, j]是否是回文子串
		vector<int> dp(n + 1); // dp[i]：从 i 开始子串的最少分割次数
		for(int i = n - 1; i >= 0; --i) {
			int temp = INT_MAX;
			for(int j = i; j < n; ++j) {
				if(ispal[i][j]) temp = min(temp, dp[j + 1]);
			}
			dp[i] = temp + 1;
		}
		return dp[0] - 1;
	}
}; // dfs改为dp

class Solution3 {
public:
	int minCut(string &s) {
		int n = s.size();
		vector<vector<bool>> ispal(n, vector<bool>(n));
		vector<int> dp(n + 1); // dp[i]：从 i 开始子串的最少分割次数
		for(int i = n - 1; i >= 0; --i) {
			ispal[i][i] = 1;
			for(int j = i + 1; j < n; ++j) { // 此处双向皆可，因为依赖的是上一行的数据
				ispal[i][j] = (s[i] == s[j]) && (i + 1 > j - 1 || ispal[i + 1][j - 1]);
			}
			int temp = INT_MAX;
			for(int j = i; j < n; ++j) {
				if(ispal[i][j]) temp = min(temp, dp[j + 1]);
			}
			dp[i] = temp + 1;
		} // ispal[i][j]：闭区间[i, j]是否是回文子串
		return dp[0] - 1;
	}
}; // 判断回文数与计算最小cut结合到同一个循环里

class Solution4 {
public:
	int minCut(string &s) {
		int n = s.size();
		vector<bool> ispal(n);
		vector<int> dp(n + 1); // dp[i]：从 i 开始子串的最少分割次数
		for(int i = n - 1; i >= 0; --i) {
			ispal[i] = 1;
			for(int j = n - 1; j >= i + 1; --j) { // 反向迭代防止覆盖ispal[j - 1]
				ispal[j] = (s[i] == s[j]) && (i + 1 > j - 1 || ispal[j - 1]);
			}
			int temp = INT_MAX;
			for(int j = i; j < n; ++j) {
				if(ispal[j]) temp = min(temp, dp[j + 1]);
			}
			dp[i] = temp + 1;
		} // ispal[i][j]：闭区间[i, j]是否是回文子串
		return dp[0] - 1;
	}
}; // 滚动数组优化

class Solution {
public:
	int minCut(string &s) {
		vector<bool> dp(s.size(), true);
		vector<int> splits(s.size());
		for(int i = 0; i < s.size(); ++i) {
			if(i > 0) splits[i] = splits[i - 1] + 1;
			for(int j = 0; j < i; ++j) {
				if(dp[j + 1] && s[i] == s[j]) {
					dp[j] = true;
					if(j == 0)
						splits[i] = 0;
					else
						splits[i] = min(splits[i], splits[j - 1] + 1);
				} else {
					dp[j] = false;
				}
			}
		}
		return splits.back();
	}
}; // 前缀切割版，可以让两个 j 的循环合为一个， splits[i]：前 i 个字符组成的子串的最少分割次数

int main() {
	Solution sol;
	string s;
	s = "aab";
	cout << sol.minCut(s) << endl; // 1
	s = "a";
	cout << sol.minCut(s) << endl; // 0
	s = "ab";
	cout << sol.minCut(s) << endl; // 1
}