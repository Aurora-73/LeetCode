#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/* 205. 同构字符串
给定两个字符串 s 和 t ，判断它们是否是同构的。
如果 s 中的字符可以按某种映射关系替换得到 t ，那么这两个字符串是同构的。
每个出现的字符都应当映射到另一个字符，同时不改变字符的顺序。不同字符不能映射到同一个字符上，相同字符只能映射到同一个字符上，字符可以映射到自己本身。*/

class Solution1 {
public:
	bool isIsomorphic(string s, string t) {
		if(s.length() != t.length()) return false;
		int map1[CHAR_MAX - CHAR_MIN + 1]; // s -> t
		int map2[CHAR_MAX - CHAR_MIN + 1]; // t -> s
		for(int i = 0; i < CHAR_MAX - CHAR_MIN; i++) {
			map1[i] = INT_MIN;
			map2[i] = INT_MIN;
		}
		for(int i = 0; i < s.length(); i++) {
			if(map1[s[i] - CHAR_MIN] == INT_MIN) {
				map1[s[i] - CHAR_MIN] = t[i];
			} else if(map1[s[i] - CHAR_MIN] != t[i]) {
				return false;
			}
			if(map2[t[i] - CHAR_MIN] == INT_MIN) {
				map2[t[i] - CHAR_MIN] = s[i];
			} else if(map2[t[i] - CHAR_MIN] != s[i]) {
				return false;
			}
		}
		return true;
	}
};

class Solution2 {
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
		vector<char> m1(256), m2(256);
		int ns = s.size(), nt = t.size();
		if(ns != nt) return false;
		for(int i = 0; i < ns; i++) {
			if(!m1[s[i]]) {
				m1[s[i]] = t[i];
			} else if(m1[s[i]] != t[i]) {
				return false;
			}
			if(!m2[t[i]]) {
				m2[t[i]] = s[i];
			} else if(m2[t[i]] != s[i]) {
				return false;
			}
		}
		return true;
	}
}; // 字符哈希表可以用数组代替

int main() {
	Solution1 sol1;
	Solution2 sol2;
	string s = "egg", t = "add";
	cout << sol1.isIsomorphic(s, t);
	cout << sol2.isIsomorphic(s, t);
	s = "foo", t = "bar";
	cout << sol1.isIsomorphic(s, t);
	cout << sol2.isIsomorphic(s, t);
}
