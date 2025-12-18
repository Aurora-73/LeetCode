// Created: 2025-12-18
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定三个字符串s1、s2、s3，请判断s3能不能由s1和s2交织（交错）组成。
两个字符串 s 和 t 交织的定义与过程如下，其中每个字符串都会被分割成若干 非空 子字符串：
	s = s1 + s2 + ... + sn
	t = t1 + t2 + ... + tm
	|n - m| <= 1
	交织 是 s1 + t1 + s2 + t2 + s3 + t3 + ... 或者 t1 + s1 + t2 + s2 + t3 + s3 + ...
提示：a + b 意味着字符串 a 和 b 连接。
示例 1：
	输入：s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
	输出：true
示例 2：
	输入：s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
	输出：false
示例 3：
	输入：s1 = "", s2 = "", s3 = ""
	输出：true
提示：
	0 <= s1.length, s2.length <= 100
	0 <= s3.length <= 200
	s1、s2、和 s3 都由小写英文字母组成 */

class Solution1 {
public:
	bool isInterleave(string &s1, string &s2, string &s3) {
		n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
		this->s1 = std::move(s1);
		this->s2 = std::move(s2);
		this->s3 = std::move(s3);
		if(n1 + n2 != n3) return false;
		return dfs(0, 0, 0);
	}

private:
	int n1, n2, n3;
	string s1, s2, s3;
	bool dfs(int i, int j, int k) {
		if(k == n3) return true;
		if(i == n1)
			return string_view(s2.begin() + j, s2.end()) == string_view(s3.begin() + k, s3.end());
		if(j == n2)
			return string_view(s1.begin() + i, s1.end()) == string_view(s3.begin() + k, s3.end());
		if(s1[i] != s3[k] && s2[j] != s3[k]) return false;
		if(s1[i] == s3[k] && s2[j] != s3[k]) return dfs(i + 1, j, k + 1);
		if(s2[j] == s3[k] && s1[i] != s3[k]) return dfs(i, j + 1, k + 1);
		return dfs(i + 1, j, k + 1) || dfs(i, j + 1, k + 1);
	}
}; // 类似于归并排序，重点在于s1[i] == s2[j] == s3[k]的时候需要分成两种情况讨论

class Solution2 {
public:
	bool isInterleave(string &s1, string &s2, string &s3) {
		int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
		if(n1 + n2 != n3) return false;
		vector<vector<bool>> dp(n1 + 1, vector<bool>(n2 + 1));
		dp[0][0] = 1;
		for(int i = 0; i < n1 && s1[i] == s3[i]; ++i) {
			dp[i + 1][0] = 1;
		} // 注意这里
		for(int j = 0; j < n2 && s2[j] == s3[j]; ++j) {
			dp[0][j + 1] = 1;
		} // 注意这里
		for(int i = 1; i < n1 + 1; ++i) {
			for(int j = 1; j < n2 + 1; ++j) {
				int k = i + j;
				if(s1[i - 1] != s3[k - 1] && s2[j - 1] != s3[k - 1])
					dp[i][j] = false;
				else if(s1[i - 1] == s3[k - 1] && s2[j - 1] != s3[k - 1])
					dp[i][j] = dp[i - 1][j];
				else if(s1[i - 1] != s3[k - 1] && s2[j - 1] == s3[k - 1])
					dp[i][j] = dp[i][j - 1];
				else
					dp[i][j] = dp[i][j - 1] || dp[i - 1][j];
			}
		}
		return dp.back().back();
	}
}; // if(s1[i - 1] != s3[k - 1] && s2[j] != s3[k]) dp[i][j] = false;
// else if(s1[i] == s3[k] && s2[j] != s3[k]) dp[i][j] = dp[i - 1][j];
// else if(s1[i] != s3[k] && s2[j] == s3[k]) dp[i][j] = dp[i][j - 1];
// else dp[i][j] = dp[i][j - 1] | dp[i - 1][j];

class Solution3 {
public:
	bool isInterleave(string &s1, string &s2, string &s3) {
		int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
		if(n1 + n2 != n3) return false;
		vector<bool> curr(n2 + 1), next(n2 + 1);
		curr[0] = 1;
		for(int j = 0; j < n2 && s2[j] == s3[j]; ++j) {
			curr[j + 1] = 1;
		} // 注意这里
		for(int i = 1; i < n1 + 1; ++i) {
			next[0] = curr[0] && (s1[i - 1] == s3[i - 1]); // 注意这里
			for(int j = 1; j < n2 + 1; ++j) {
				int k = i + j;
				if(s1[i - 1] != s3[k - 1] && s2[j - 1] != s3[k - 1])
					next[j] = false;
				else if(s1[i - 1] == s3[k - 1] && s2[j - 1] != s3[k - 1])
					next[j] = curr[j];
				else if(s1[i - 1] != s3[k - 1] && s2[j - 1] == s3[k - 1])
					next[j] = next[j - 1];
				else
					next[j] = next[j - 1] || curr[j];
			}
			swap(curr, next);
		}
		return curr.back();
	}
}; // 滚动数组优化

class Solution {
public:
	bool isInterleave(string &s1, string &s2, string &s3) {
		int n1 = s1.size(), n2 = s2.size(), n3 = s3.size();
		if(n1 + n2 != n3) return false;
		vector<bool> dp(n2 + 1);
		dp[0] = true;
		for(int j = 0; j < n2; ++j) dp[j + 1] = dp[j] && s2[j] == s3[j];
		for(int i = 1; i <= n1; ++i) {
			dp[0] = dp[0] && s1[i - 1] == s3[i - 1];
			for(int j = 1; j <= n2; ++j) {
				int k = i + j - 1;
				dp[j] = (dp[j] && s1[i - 1] == s3[k]) || (dp[j - 1] && s2[j - 1] == s3[k]);
			}
		}
		return dp.back();
	}
}; // 单数组优化

int main() {
	Solution sol;
	string s1, s2, s3;
	s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac";
	cout << sol.isInterleave(s1, s2, s3) << endl;
	s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc";
	cout << sol.isInterleave(s1, s2, s3) << endl;
	s1 = "", s2 = "", s3 = "";
	cout << sol.isInterleave(s1, s2, s3) << endl;
}