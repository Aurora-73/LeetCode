// Created: 2025-06-05
#include "MyUtils.hpp"

/*1312. 让字符串成为回文串的最少插入次数
给你一个字符串 s ，每一次操作你都可以在字符串的任意位置插入任意字符。
请你返回让 s 成为回文串的 最少操作次数 。
「回文串」是正读和反读都相同的字符串。
示例 1：
    输入：s = "zzazz"
    输出：0
    解释：字符串 "zzazz" 已经是回文串了，所以不需要做任何插入操作。
示例 2：
    输入：s = "mbadm"
    输出：2
    解释：字符串可变为 "mbdadbm" 或者 "mdbabdm" 。
示例 3：
    输入：s = "leetcode"
    输出：5
    解释：插入 5 个字符后字符串变为 "leetcodocteel" 。
提示：
    1 <= s.length <= 500
    s 中所有字符都是小写字母。*/

class Solution {
public:
	int minInsertions(string &s) {
		int n = s.size();
		std::vector<int> dp(n + 1, 0);
		for(int i = n - 1; i >= 0; --i) {
			int prev = 0;
			for(int j = n - 1; j >= 0; --j) {
				int temp = dp[j];
				if(s[i] == s[n - j - 1]) {
					dp[j] = prev + 1;
				} else {
					dp[j] = std::max(dp[j], dp[j + 1]);
				}
				prev = temp;
			}
		}
		return n - dp[0];
	}
}; // n - （自身 和 翻转）的 最长公共子序列

class Solution {
public:
	int minInsertions(const string &s) {
		int n = s.size();
		if(n <= 1) return 0;

		// f[i][j] 表示将子串 s[i..j] 变为回文所需的最少插入次数
		vector<vector<int>> f(n, vector<int>(n, 0));

		// 从下往上、从左到右地填表
		for(int i = n - 1; i >= 0; --i) {
			for(int j = i + 1; j < n; ++j) {
				if(s[i] == s[j]) {
					// 两端字符相同，无需额外插入，继承内部子问题
					f[i][j] = f[i + 1][j - 1];
				} else {
					// 否则，在“去掉左端”或“去掉右端”两种选择中取最小，再加 1
					f[i][j] = min(f[i + 1][j], f[i][j - 1]) + 1;
				}
			}
		}

		return f[0][n - 1];
	}
};

class Solution {
public:
	int minInsertions(const string &s) {
		int n = s.size();
		if(n <= 1) return 0;

		// 用一维 dp 数组代替二维 f 矩阵：
		// dp[j] 表示当前 i 行的 f[i][j]，
		// 在遍历 i 过程中，dp[j] 的值会不断被更新。
		vector<int> dp(n, 0);

		// 自底向上枚举 i，从 n-2 到 0
		for(int i = n - 2; i >= 0; --i) {
			// prev 存储 “上一行（i+1）”的 f[i+1][j-1]，
			// 初始时对应 j = i+1 时的 f[i+1][i] = 0
			int prev = 0;

			// 遍历 j 从 i+1 到 n-1（因为 j == i 时 f[i][i] = 0）
			for(int j = i + 1; j < n; ++j) {
				// temp 暂存 “上一行 f[i+1][j]” 的值，
				// 下一轮循环时会作为 prev 使用
				int temp = dp[j];

				if(s[i] == s[j]) {
					// 如果两端字符相同，就继承 f[i+1][j-1]，
					// 也就是 prev
					dp[j] = prev;
				} else {
					// 否则，取 f[i+1][j]（temp） 和 f[i][j-1]（dp[j-1]）的较小值 + 1
					dp[j] = min(temp, dp[j - 1]) + 1;
				}

				// 更新 prev = 原来的 f[i+1][j]
				prev = temp;
			}
		}

		// 最终 dp[n-1] 存的就是 f[0][n-1]
		return dp[n - 1];
	}
};

int main() {
	Solution sol;
}