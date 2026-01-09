// Created: 2025-04-19
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定一个字符串 s，请你找出其中不含有重复字符的最长 子串的长度。
示例1:
    输入: s = "abcabcbb"
    输出: 3 
    解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。注意 "bca" 和 "cab" 也是正确答案。
示例 2:
	输入: s = "bbbbb"
	输出: 1
	解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
示例 3:
	输入: s = "pwwkew"
	输出: 3
	解释: 因为无重复字符的最长子串是"wke"，所以其长度为 3。
	    请注意，你的答案必须是 子串 的长度，"pwke"是一个子序列，不是子串。
提示：
	0 <= s.length <= 5 * 10^4
	s由英文字母、数字、符号和空格组成
	给定一个字符串 s，请你找出其中不含有重复字符的最长 子串的长度。 */

class Solution1 {
public:
	int lengthOfLongestSubstring(string &s) {
		if(s.size() == 0) return 0;
		unordered_set<char> sett { s[0] };
		int i = 0, j = 0, len = 1;
		while(j < s.size()) {
			j++;
			if(j < s.size()) {
				while(sett.count(s[j])) {
					sett.erase(s[i]);
					i++;
				}
				sett.insert(s[j]);
			}
			len = max(len, int(sett.size()));
		}
		return len;
	}
};

class Solution {
public:
	int lengthOfLongestSubstring(string &s) {
		int res = 0, i = 0, n = s.size();
		array<bool, 256> exsit {};
		for(int j = 0; j < n; ++j) {
			int index = s[j] - CHAR_MIN;
			while(exsit[index]) {
				exsit[s[i++] - CHAR_MIN] = 0;
			}
			exsit[index] = 1;
			if(j - i + 1 > res) {
				res = j - i + 1;
			}
		}
		return res;
	}
};

int main() {
	Solution sol;
	string s;
	s = "abcabcbb"; // 3
	cout << sol.lengthOfLongestSubstring(s) << endl;
	s = "bbbbb"; // 1
	cout << sol.lengthOfLongestSubstring(s) << endl;
	s = "pwwkew"; // 3
	cout << sol.lengthOfLongestSubstring(s) << endl;
}