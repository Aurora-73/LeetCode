// Created: 2025-12-28
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个布尔表达式和一个期望的布尔结果 result，
布尔表达式由 0 (false)、1 (true)、& (AND)、 | (OR) 和 ^ (XOR) 符号组成。
实现一个函数，算出有几种可使该表达式得出 result 值的括号方法。
示例 1：
	输入：s = "1^0|0|1", result = 0
	输出：2
	解释：两种可能的括号方法是
	1^(0|(0|1))
	1^((0|0)|1)
示例 2：
	输入：s = "0&0&0&1^1|0", result = 1
	输出：10
提示：
	运算符的数量不超过 19 个 */

class Solution {
public:
	int countEval(string &s, int target) {
		int n = s.size();
		if(n < 2) return n && s[0] == target + '0';
		vector<vector<array<int, 2>>> dp(n, vector<array<int, 2>>(n));
		for(int i = 0; i < n; i += 2) {
			dp[i][i][s[i] - '0'] = 1;
		}
		for(int diff = 2; diff < n; diff += 2) {
			for(int i = 0; diff + i < n; i += 2) {
				for(int k = i + 1, j = diff + i; k < j; k += 2) {
					int LF = dp[i][k - 1][0], RF = dp[k + 1][j][0];
					int LT = dp[i][k - 1][1], RT = dp[k + 1][j][1];
					if(s[k] == '^') {
						dp[i][j][0] += LF * RF + LT * RT;
						dp[i][j][1] += LF * RT + LT * RF;
					} else if(s[k] == '|') {
						dp[i][j][0] += LF * RF;
						dp[i][j][1] += LT * RF + LF * RT + LT * RT;
					} else if(s[k] == '&') {
						dp[i][j][0] += LF * RF + LF * RT + LT * RF;
						dp[i][j][1] += LT * RT;
					} else {
						throw std::runtime_error("Input Error!");
					}
				}
			}
		}
		return dp[0][n - 1][target];
	}
}; // dp[i][j][0/1] = 子表达式 s[i..j] 通过某种括号方式得到 0 / 1 的方案数
// 状态数 O(n^2)，每个状态枚举切分点 O(n) => 时间 O(n^3) 空间 O(n^2)
// dp[i][j]计算：枚举s[i..j]的每个运算，对于左右两个字串的表达式进行计算，得到当前值
// int l0 = dp[i][k - 1][0], r0 = dp[k + 1][j][0], l1 = dp[i][k - 1][1], r1 = dp[k + 1][j][1];
// for(k : [i...j])
//	  if(s[k] == '^') dp[i][j][0] = l0 * r0 + l1 * r1,  dp[i][j][1] = l0 * r1 + l1 * r0;
//	  if(s[k] == '|') dp[i][j][0] = l0 * r0,  dp[i][j][1] = l1 * r0 + l0 * r1 + l1 * r1;
//	  if(s[k] == '&') dp[i][j][0] = l0 * r0 + l0 * r1 + l1 * r0,  dp[i][j][1] = l1 * r1;

int main() {
	Solution sol;
	string s;
	int result;

	s = "1^0|0|1", result = 0;
	cout << sol.countEval(s, result) << endl; // 2

	s = "0&0&0&1^1|0", result = 1;
	cout << sol.countEval(s, result) << endl; // 10
}