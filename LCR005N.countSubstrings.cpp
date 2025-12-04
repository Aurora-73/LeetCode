// Created: 2025-12-01
#include "MyUtils.hpp"

/* 给定一个字符串 s，请计算这个字符串中有多少个回文子字符串。
具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串。
示例 1：
	输入：s = "abc"
	输出：3
	解释：三个回文子串: "a", "b", "c"
示例 2：
	输入：s = "aaa"
	输出：6
	解释：6个回文子串: "a", "a", "a", "aa", "aa", "aaa"
提示：
	1 <= s.length <= 1000
	s 由小写英文字母组成
注意：本题与主站 70 题相同： */

class Solution {
public:
	int countSubstrings(const string &s) {
		int n = s.size(), res = 0; // 初始包含全部长为1的
		for(int i = 0; i < n; ++i) {
			for(int l = 0; l <= min(i, n - i); ++l) {
				if(s[i - l] != s[i + l]) {
					break;
				}
				++res;
			} // 奇数
			for(int l = 0; l <= min(i, n - i); ++l) {
				if(s[i - l] != s[i + 1 + l]) {
					break;
				}
				++res;
			} // 偶数
		}
		return res;
	}
};

int main() {
	Solution sol;
	string s;
	s = "abc";
	cout << sol.countSubstrings(s) << endl;
	s = "aaa";
	cout << sol.countSubstrings(s) << endl;
}