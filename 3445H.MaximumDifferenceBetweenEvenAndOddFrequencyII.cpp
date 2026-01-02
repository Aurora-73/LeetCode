// Created: 2025-06-11
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 3445. 奇偶频次间的最大差值 II
给你一个字符串s和一个整数k。
请你找出 s的子字符串 subs 中两个字符的出现频次之间的最大差值，freq{a} - freq{b}，其中：
	subs的长度至少为k。
	字符a在subs中出现奇数次。
	字符b在subs中出现偶数次。
返回 最大 差值。
注意，subs可以包含超过 2 个 互不相同 的字符。.
子字符串是字符串中的一个连续字符序列。
示例 1：
	输入：s = "12233", k = 4
	输出：-1
	解释：
	对于子字符串"12233"，"1"的出现次数是 1，"3"的出现次数是2。差值是1 - 2 = -1。
示例 2：
	输入：s = "1122211", k = 3
	输出：1
	解释：
	对于子字符串"11222"，"2"的出现次数是 3，"1"的出现次数是 2。差值是3 - 2 = 1。
示例 3：
	输入：s = "110", k = 3
	输出：-1
提示：
	3 <= s.length <= 3 * 10^4
	s仅由数字"0"到"4"组成。
	输入保证至少存在一个子字符串是由一个出现奇数次的字符和一个出现偶数次的字符组成。
	1 <= k <= s.length */

class Solution1 {
public:
	int maxDifference(string &s, int k) {
		array<int, 5> freqs;
		int n = s.size();
		long long maxDiff = numeric_limits<int>::min();
		for(int i = 0; i < n - k + 1; ++i) {
			freqs.fill(0);
			int j = i, noNeadMatch = max(i + k - 1, i + int(maxDiff));
			for(; j < noNeadMatch; ++j) {
				int val = s[j] - '0';
				++freqs[val];
			}
			for(; j < n; ++j) {
				int val = s[j] - '0';
				++freqs[val];
				int maxa = numeric_limits<int>::min(), minb = numeric_limits<int>::max();
				for(auto freq : freqs) {
					if(freq != 0) {
						if(freq % 2) {
							maxa = max(maxa, freq);
						} else {
							minb = min(minb, freq);
						}
					}
				}
				maxDiff = max(maxDiff, static_cast<long long>(maxa) - minb);
			}
		}
		return maxDiff;
	} // 奇 - 偶 的最大值
};

class Solution {
public:
	int maxDifference(string &s, int k) {
		int n = s.size();
		vector<array<int, 5>> freqs(n + 1); // 前缀和不包含自身
		freqs[0].fill(0);
		for(int i = 1; i <= n; ++i) {
			freqs[i] = freqs[i - 1];
			++freqs[i][s[i - 1] - '0'];
		}
		long long res = numeric_limits<int>::min();
		for(int i = 0; i <= n - k; ++i) {
			for(int j = i + k; j <= n; ++j) {
				int maxa = numeric_limits<int>::min(), minb = numeric_limits<int>::max();
				for(int m = 0; m < 5; ++m) {
					int count = freqs[j][m] - freqs[i][m];
					if(count % 2) {
						maxa = max(maxa, count);
					} else if(count) {
						minb = min(minb, count);
					}
				}
				res = max(res, static_cast<long long>(maxa) - minb);
			}
		}
		return res;
	} // 奇 - 偶 的最大值
};

int main() {
	Solution sol;
	string s;
	int k;
	s = "12233", k = 4;
	cout << sol.maxDifference(s, k) << endl; // -1
	s = "1122211", k = 3;
	cout << sol.maxDifference(s, k) << endl; // 1
	s = "110", k = 3;
	cout << sol.maxDifference(s, k) << endl; // -1
}