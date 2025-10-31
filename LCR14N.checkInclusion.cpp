// Created: 2025-10-29
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定两个字符串s1和s2，写一个函数来判断 s2 是否包含 s1的某个变位词。
换句话说，第一个字符串的排列之一是第二个字符串的 子串。
示例 1：
	输入: s1 = "ab" s2 = "eidbaooo"
	输出: True
	解释: s2 包含 s1 的排列之一 ("ba").
示例 2：
	输入: s1= "ab" s2 = "eidboaoo"
	输出: False
提示：
	1 <= s1.length, s2.length <= 10^4
	s1 和 s2 仅包含小写字母
注意：本题与主站 567题相同： */

class Solution1 {
public:
	bool checkInclusion(string &s1, string &s2) {
		if(s1.size() > s2.size()) {
			return false;
		}
		int count[26] { 0 }, n1 = s1.size(), n2 = s2.size(), cnt = 0;
		for(auto c : s1) {
			count[c - 'a']++;
		}
		for(int i = 0; i < n1; ++i) {
			if(--count[s2[i] - 'a'] >= 0) {
				cnt++;
			}
		}
		for(int i = n1; i < n2; ++i) {
			if(cnt == n1) {
				return true;
			}
			if(++count[s2[i - n1] - 'a'] > 0) {
				cnt--;
			}
			if(--count[s2[i] - 'a'] >= 0) {
				cnt++;
			}
		}
		return cnt == n1;
	}
}; // 在s2中设置一个与s1等长的窗口，统计其中每个字母的出现次数，然后向右滑动，cnt记录成功匹配的元素个数

class Solution {
public:
	bool checkInclusion(string &s1, string &s2) {
		if(s1.size() > s2.size()) {
			return false;
		}
		int differ[26] {}, notZero = 0, n1 = s1.size(), n2 = s2.size();
		for(int i = 0; i < n1; ++i) {
			differ[s1[i] - 'a']++;
		}
		for(int i = 0; i < n1; ++i) {
			differ[s2[i] - 'a']--;
		}
		for(auto d : differ) {
			if(d != 0) ++notZero;
		}
		if(notZero == 0) {
			return true;
		}
		for(int i = n1; i < n2; ++i) {
			int in = s2[i] - 'a', out = s2[i - n1] - 'a';
			if(differ[in] == 0) {
				++notZero;
			}
			--differ[in];
			if(differ[in] == 0) {
				--notZero;
			}
			if(differ[out] == 0) {
				++notZero;
			}
			++differ[out];
			if(differ[out] == 0) {
				--notZero;
			}
			if(notZero == 0) {
				return true;
			}
		}
		return false;
	}
}; // 直接用notZero可以更简单

int main() {
	Solution sol;
	string s1, s2;
	s1 = "ab", s2 = "eidbaooo";
	cout << sol.checkInclusion(s1, s2) << endl; // T
	s1 = "ab", s2 = "eidboaoo";
	cout << sol.checkInclusion(s1, s2) << endl; // F
}