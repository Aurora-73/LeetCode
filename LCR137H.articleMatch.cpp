// Created: 2025-07-01
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* LCR 137. 模糊搜索验证
请设计一个程序来支持用户在文本编辑器中的模糊搜索功能。
用户输入内容中可能使用到如下两种通配符：
	"." 匹配任意单个字符。
	"*" 匹配零个或多个前面的那一个元素。
请返回用户输入内容 input 所有字符是否可以匹配原文字符串 article。
示例 1：
	输入：article = "aa", input = "a"
	输出：false
	解释："a" 无法匹配 "aa" 整个字符串。
示例 2：
	输入：article = "aa", input = "a*"
	输出：true
	解释：因为 "*" 代表可以匹配零个或多个前面的那一个元素, 在这里前面的元素就是 "a"。
	因此，字符串 "aa" 可被视为 "a" 重复了一次。
	示例3：
	输入：article = "ab", input = ".*"
	输出：true
	解释：".*" 表示可匹配零个或多个（"*"）任意字符（"."）。
提示：
	1 <= article.length <= 20
	1 <= input.length <= 20
	article 只包含从 a-z 的小写字母。
	input 只包含从 a-z 的小写字母，以及字符 . 和 *。
	保证每次出现字符 * 时，前面都匹配到有效的字符 */

class Solution1 {
public:
	bool articleMatch(string &s, string &p) {
		int m = s.size(), n = p.size();
		vector<vector<bool>> dp(m + 1, vector<bool>(n + 1));
		auto equal = [&](int i, int j) {
			return s[i] == p[j] || p[j] == '.';
		};
		dp[0][0] = 1;
		for(int j = 2; j <= n && p[j - 1] == '*'; j += 2) {
			dp[0][j] = true;
		} // 空字符串仅能和全(?*)的字符串匹配
		for(int i = 1; i <= m; ++i) {
			for(int j = 1; j <= n; ++j) {
				if(p[j - 1] != '*') {
					dp[i][j] = dp[i - 1][j - 1] && equal(i - 1, j - 1);
				} else {
					dp[i][j] = dp[i][j - 2] || (dp[i - 1][j] && equal(i - 1, j - 2));
				}
			}
		}
		return dp.back().back();
	}
};

class Solution {
public:
	bool articleMatch(string &s, string &p) {
		int m = s.size(), n = p.size();
		vector<bool> now(n + 1), prev(n + 1);
		now[0] = 1;
		for(int j = 2; j <= n && p[j - 1] == '*'; j += 2) {
			now[j] = true;
		}
		auto equal = [&](int i, int j) {
			return s[i] == p[j] || p[j] == '.';
		}; // 空字符串仅能和全(?*)的字符串匹配
		for(int i = 1; i <= m; ++i) {
			// prev = std::move(now);
			// now = vector<bool>(n + 1); 与下面两行等效
			std::swap(now, prev);  // now 除了[0]的值无所谓
			if(i == 2) now[0] = 0; // 必须去掉 dp[0][0] 的置位
			for(int j = 1; j <= n; ++j) {
				if(p[j - 1] != '*') {
					now[j] = prev[j - 1] && equal(i - 1, j - 1);
				} else {
					now[j] = now[j - 2] || (prev[j] && equal(i - 1, j - 2));
				}
			}
		}
		return now.back();
	}
};

/* 推导思路
假设 p[j-1] == '*'，那么在模式里 '*' 的前一个字符就是 p[j-2]（记作 x）。我们要让 s[0..i-1] 和 p[0..j-3] + x* 匹配，于是有两种互斥的可能：
情况 A：* 匹配 “零次” x
    既然不需要用任何 x，就相当于直接把模式末尾的 x* 整块“扔掉”。
    剩下的问题就变成：s[0..i-1] 能否被 p[0..j-3] 匹配？
    对应到 DP，就是 dp[i][j] = dp[i][j-2];
    这里的 j-2 刚好跳过了 x* 这两个字符。
情况 B：* 至少匹配 “一次” x
    既然要至少用到一个 x，那么：
    s[i-1] 必须要“能和 x 匹上” —— 也就是 s[i-1] == p[j-2]  或者  p[j-2] == '.'
    去掉 s 末尾的这个字符 s[i-1] 后（长度从 i 变成 i-1），剩下的 s[0..i-2] 依然要被整个模式 p[0..j-1]（即原来的 …x*）匹配。
    也就是说，我们在 dp[i-1][j] 的基础上“再吃”一个 x。
    合起来就是 dp[i][j] = dp[i-1][j] && (s[i-1] == p[j-2] || p[j-2] == '.'); */

int main() {
	Solution sol;
	string s, p;
	s = "aab", p = "c*a*b";
	cout << sol.articleMatch(s, p) << endl; // 1
	s = "aa", p = "a";
	cout << sol.articleMatch(s, p) << endl; // 0
	s = "aa", p = "a*";
	cout << sol.articleMatch(s, p) << endl; // 1
	s = "ab", p = ".*";
	cout << sol.articleMatch(s, p) << endl; // 1
}