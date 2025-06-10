// Created: 2025-06-10
#include "MyDateGen.h"
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 438. 找到字符串中所有字母异位词
给定两个字符串 s 和 p，找到 s 中所有 p 的异位词的子串，返回这些子串的起始索引。
不考虑答案输出的顺序。
示例1:
输入: s = "cbaebabacd", p = "abc"
输出: {0,6}
解释:
起始索引等于 0 的子串是 "cba", 它是 "abc" 的异位词。
起始索引等于 6 的子串是 "bac", 它是 "abc" 的异位词。
示例 2:
	输入: s = "abab", p = "ab"
	输出: {0,1,2}
	解释:
	起始索引等于 0 的子串是 "ab", 它是 "ab" 的异位词。
	起始索引等于 1 的子串是 "ba", 它是 "ab" 的异位词。
	起始索引等于 2 的子串是 "ab", 它是 "ab" 的异位词。
提示:
	1 <= s.length, p.length <= 3 * 10^4
	s和p仅包含小写字母 */

class Solution1 {
public:
	vector<int> findAnagrams(string &s, string &p) {
		int n = s.size(), pn = p.size();
		if(pn > n) {
			return {};
		}
		vector<int> res;
		array<unsigned, 26> set;
		set.fill(0);
		for(auto c : p) {
			++set[c - 'a'];
		}
		for(int i = 0; i < n; ++i) {
			array<unsigned, 26> subSet = set;
			int count = 0;
			for(int j = i; j < n; ++j) {
				if(subSet[s[j] - 'a']) {
					subSet[s[j] - 'a']--;
					++count;
				} else {
					if(set[s[j] - 'a']) {
						while(s[i] != s[j]) {
							i++;
						}
					} else {
						i = j;
					}
					break;
				}
				if(count == pn) {
					res.push_back(i);
					break;
				}
			}
		}
		return res;
	}
}; // 没有真正的"滑动"，滑动窗口要利用之前已经数过的数，并且逻辑太复杂

class Solution2 {
public:
	vector<int> findAnagrams(string &s, string &p) {
		int n = s.size(), m = p.size();
		if(m > n) return {};
		array<int, 26> cntP { 0 }, cntS { 0 };
		for(char c : p) cntP[c - 'a']++;
		vector<int> res;
		// 先把 s[0..m-1] 这一窗口统计进来
		for(int i = 0; i < m; ++i) {
			cntS[s[i] - 'a']++;
		}
		// 如果一开始就相等，记录 0
		if(cntS == cntP) res.push_back(0);
		// 从 i = m 开始往右滑，每次移除最左一个，加上当前字符
		for(int i = m; i < n; ++i) {
			cntS[s[i] - 'a']++;
			cntS[s[i - m] - 'a']--;
			if(cntS == cntP) {
				res.push_back(i - m + 1);
			}
		}
		return res;
	}
}; // 定长滑动窗口

class Solution3 {
public:
	vector<int> findAnagrams(string &s, string &p) {
		vector<int> ans;
		int cnt[26] {};
		for(char c : p) {
			cnt[c - 'a']++;
		}
		int left = 0, sn = s.size(), pn = p.size();
		for(int right = 0; right < sn; right++) {
			int c = s[right] - 'a';
			cnt[c]--;           // 右端点字母进入窗口
			while(cnt[c] < 0) { // 字母 c 太多了
				cnt[s[left] - 'a']++;
				left++;
			}
			// s' 和 p 的每种字母的出现次数都相同，不需要计数，直接长度比较即可
			if(right - left + 1 == pn) {
				ans.push_back(left);
			}
		}
		return ans;
	}
}; // 不定长滑动窗口

int main() {
	Solution2 sol2;
	Solution3 sol3;
	string s, p;
	s = "cbaebabacd", p = "abc";
	cout << sol2.findAnagrams(s, p) << endl;
	cout << sol3.findAnagrams(s, p) << endl;
	s = "abab", p = "ab";
	cout << sol2.findAnagrams(s, p) << endl;
	cout << sol3.findAnagrams(s, p) << endl;
}