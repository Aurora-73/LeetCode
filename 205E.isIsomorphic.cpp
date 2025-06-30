// Created: 2025-06-30
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 205. 同构字符串
给定两个字符串 s 和 t ，判断它们是否是同构的。
如果 s 中的字符可以按某种映射关系替换得到 t ，那么这两个字符串是同构的。
每个出现的字符都应当映射到另一个字符，同时不改变字符的顺序。
不同字符不能映射到同一个字符上，相同字符只能映射到同一个字符上，字符可以映射到自己本身。
提示：
	1 <= s.length <= 5 * 104
	t.length == s.length
	s 和 t 由任意有效的 ASCII 字符组成*/

class Solution1 {
public:
	bool isIsomorphic(string s, string t) {
		unordered_map<char, char> m1, m2;
		if(s.length() != t.length()) return false;
		for(int i = 0; i < s.length(); i++) {
			if(m1.find(s[i]) == m1.end()) {
				m1[s[i]] = t[i];
			} else if(m1[s[i]] != t[i]) {
				return false;
			}
			if(m2.find(t[i]) == m2.end()) {
				m2[t[i]] = s[i];
			} else if(m2[t[i]] != s[i]) {
				return false;
			}
		}
		return true;
	}
};

class Solution {
public:
	bool isIsomorphic(string s, string t) {
		if(s.length() != t.length()) return false;
		array<char, 128> map1, map2; // ASCII字符的范围一定是 0 - 127
		map1.fill(-1), map2.fill(-1);
		for(int i = 0; i < s.length(); i++) {
			if(map1[s[i]] == -1) {
				map1[s[i]] = t[i];
			} else if(map1[s[i]] != t[i]) {
				return false;
			}
			if(map2[t[i]] == -1) {
				map2[t[i]] = s[i];
			} else if(map2[t[i]] != s[i]) {
				return false;
			}
		}
		return true;
	}
}; // 字符哈希表可以用数组代替

int main() {
	Solution1 sol1;
	Solution sol;
	string s = "egg", t = "add";
	cout << sol1.isIsomorphic(s, t);
	cout << sol.isIsomorphic(s, t) << endl;
	s = "foo", t = "bar";
	cout << sol1.isIsomorphic(s, t);
	cout << sol.isIsomorphic(s, t);
}
