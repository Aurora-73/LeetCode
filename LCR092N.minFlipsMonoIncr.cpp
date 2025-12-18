// Created: 2025-12-18
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 如果一个由"0" 和 "1"组成的字符串，
是以一些 "0"（可能没有 "0"）后面跟着一些 "1"（也可能没有 "1"）的形式组成的，那么该字符串是单调递增的。
我们给出一个由字符 "0" 和 "1"组成的字符串 s，我们可以将任何"0" 翻转为"1"或者将"1"翻转为"0"。
返回使 s单调递增的最小翻转次数。
示例 1：
	输入：s = "00110"
	输出：1
	解释：我们翻转最后一位得到 00111.
示例 2：
	输入：s = "010110"
	输出：2
	解释：我们翻转得到 011111，或者是 000111。
示例 3：
	输入：s = "00011000"
	输出：2
	解释：我们翻转得到 00000000。
提示：
	1 <= s.length <= 20000
	s 中只包含字符"0"和"1" */

class Solution1 {
public:
	int minFlipsMonoIncr(string &s) {
		int n = s.size();
		return min(dfs(s, n - 1, '0'), dfs(s, n - 1, '1'));
	}

private:
	int dfs(string &s, int i, char needVal) {
		if(i == 0) return s[0] != needVal;
		if(needVal == '1') {
			return min(dfs(s, i - 1, '0'), dfs(s, i - 1, '1')) + (s[i] != '1');
		} else {
			return dfs(s, i - 1, '0') + (s[i] != '0');
		}
	}
	// dfs(i)返回前i个字符单调递增的翻转次数，
	// 则dfs(i + 1)有两种情况：1、s[i + 1]变为1则只需要前面的单调即可, 2、s[i + 1]变为0，前面的也都要变为0
};

class Solution2 {
public:
	int minFlipsMonoIncr(string &s) {
		vector<array<int, 2>> dp;
		int n = s.size();
		dp.resize(n);
		dp[0][0] = s[0] != '0';
		dp[0][1] = s[0] != '1';
		for(int i = 1; i < n; ++i) {
			dp[i][0] = dp[i - 1][0] + (s[i] != '0');
			dp[i][1] = min(dp[i - 1][0], dp[i - 1][1]) + (s[i] != '1');
		}
		return min(dp.back()[0], dp.back()[1]);
	}
}; // dp[i][j] 记录若s[i]最终为j，则前i个字符单调递增需要的翻转次数

class Solution {
public:
	int minFlipsMonoIncr(string &s) {
		array<int, 2> curr, prev;
		int n = s.size();
		prev[0] = s[0] != '0';
		prev[1] = s[0] != '1';
		for(int i = 1; i < n; ++i) {
			curr[0] = prev[0] + (s[i] != '0');
			curr[1] = min(prev[0], prev[1]) + (s[i] != '1');
			prev = curr;
		}
		return min(curr[0], curr[1]);
	}
}; // 滚动数组优化

int main() {
	Solution sol;
	string s;
	s = "00110";
	cout << sol.minFlipsMonoIncr(s) << endl;
	s = "010110";
	cout << sol.minFlipsMonoIncr(s) << endl;
	s = "00011000";
	cout << sol.minFlipsMonoIncr(s) << endl;
}