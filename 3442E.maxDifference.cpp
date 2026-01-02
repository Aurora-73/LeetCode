// Created: 2025-06-10
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 3442. 奇偶频次间的最大差值 I
给你一个由小写英文字母组成的字符串s。
请你找出字符串中两个字符 a1 和 a2 的出现频次之间的 最大 差值 diff = a1 - a2，这两个字符需要满足：
	a1在字符串中出现 奇数次。
	a2在字符串中出现 偶数次。
返回 最大 差值。
示例 1：
	输入：s = "aaaaabbc"
	输出：3
	解释：
	字符"a"出现 奇数次，次数为5 ；字符"b"出现 偶数次，次数为2。
	最大差值为5 - 2 = 3。
示例 2：
	输入：s = "abcabcab"
	输出：1
	解释：
	字符 "a" 出现 奇数次，次数为3 ；字符"c"出现 偶数次，次数为2。
	最大差值为3 - 2 = 1。
提示：
	3 <= s.length <= 100
	s仅由小写英文字母组成。
	s至少由一个出现奇数次的字符和一个出现偶数次的字符组成。 */

class Solution1 {
public:
	int maxDifference(string &s) {
		unordered_map<char, int> map;
		for(auto c : s) {
			++map[c];
		}
		int a1 = 0, a2 = numeric_limits<int>::max();
		for(auto &pair : map) {
			int a = pair.second;
			if(a % 2) {
				a1 = max(a1, a);
			} else {
				a2 = min(a2, a);
			}
		}
		return a1 - a2;
	}
};

class Solution {
public:
	int maxDifference(string &s) {
		array<int, 26> map;
		map.fill(0);
		for(auto c : s) {
			++map[c - 'a'];
		}
		int a1 = 0, a2 = numeric_limits<int>::max();
		for(auto a : map) {
			if(a != 0) {
				if(a % 2) {
					a1 = max(a1, a);
				} else {
					a2 = min(a2, a);
				}
			}
		}
		return a1 - a2;
	}
}; // 仅含有小写字母的哈希表可以用数组代替

int main() {
	Solution sol;
	string s;
	s = "aaaaabbc";
	cout << sol.maxDifference(s) << endl; // 输出 3
	s = "abcabcab";
	cout << sol.maxDifference(s) << endl; // 输出 1
}