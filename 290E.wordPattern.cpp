// Created: 2025-06-30
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

using namespace std;

/* 给定一种规律 pattern 和一个字符串 s ，判断 s 是否遵循相同的规律。
这里的 遵循 指完全匹配，例如， pattern 里的每个字母和字符串 s 中的每个非空单词之间存在着双向连接的对应规律。
示例1:
输入: pattern = "abba", s = "dog cat cat dog"
输出: true
示例 2:
输入:pattern = "abba", s = "dog cat cat fish"
输出: false
示例 3:
输入: pattern = "aaaa", s = "dog cat cat dog"
输出: false */

class Solution1 {
public:
	bool wordPattern(string pattern, string s) {
		stringstream ss(s);
		unordered_map<char, string> m1;
		unordered_map<string, char> m2;
		string temp;
		for(auto c : pattern) {
			if(!(ss >> temp)) return false;
			if(m1.find(c) == m1.end()) {
				m1[c] = temp;
			} else if(m1[c] != temp) {
				return false;
			}
			if(m2.find(temp) == m2.end()) {
				m2[temp] = c;
			} else if(m2[temp] != c) {
				return false;
			}
		}
		if(ss >> temp) return false;
		return true;
	}
};

class Solution2 {
public:
	bool wordPattern(string pattern, string s) {
		size_t i = 0;
		unordered_map<string, char> m2;
		string temp;
		for(auto c : pattern) {
			if(!line2string(s, temp, i)) return false;
			if(m2.find(temp) == m2.end()) {
				m2[temp] = c;
			} else if(m2[temp] != c) {
				return false;
			}
		}
		if(line2string(s, temp, i)) return false;
		vector<bool> unique(128, false);
		for(auto par : m2) {
			if(unique[par.second]) return false;
			unique[par.second] = true;
		}
		return true;
	}

private:
	bool line2string(const string &line, string &str, size_t &i) {
		str = "";
		if(line[i] == ' ') i++;
		for(; i < line.length(); i++) {
			if(line[i] != ' ') {
				str.push_back(line[i]);
			} else {
				i++;
				break;
			}
		}
		return str.length();
	}
};

class Solution3 {
public:
	bool wordPattern(string pattern, string s) {
		size_t i = 0;
		size_t j = 0;
		unordered_set<char> set;
		unordered_map<string, char> m;
		for(auto c : pattern) {
			if(j >= s.size()) return false;
			while(j < s.size() && s[j] != ' ') j++;
			const string &temp = s.substr(i, j - i);
			i = j + 1;
			j = i;
			if(m.find(temp) == m.end()) {
				m[temp] = c;
			} else if(m[temp] != c) {
				return false;
			}
		}
		if(j < s.size()) return false;
		for(auto par : m) {
			if(set.find(par.second) != set.end()) return false;
			set.insert(par.second);
		}
		return true;
	}
};

class Solution {
public:
	bool wordPattern(string &pattern, string &s) {
		size_t i = 0, j = 0;
		string_view sv(s);
		vector<bool> set(26);
		unordered_map<string_view, char> m;
		for(auto c : pattern) {
			if(j >= s.size()) return false;
			while(j < s.size() && s[j] != ' ') j++;
			string_view temp = sv.substr(i, j - i);
			i = j + 1;
			j = i;
			if(m.find(temp) == m.end()) {
				m[temp] = c;
			} else if(m[temp] != c) {
				return false;
			}
		}
		if(j < s.size()) return false;
		for(auto par : m) {
			if(set[par.second - 'a']) return false;
			set[par.second - 'a'] = 1;
		}
		return true;
	}
}; // 仅含小写字母的哈希表可以用数组代替，然后用string_view进行优化

int main() {
	Solution1 sol1;
	Solution2 sol2;
	Solution sol3;
	string pattern = "abba", s = "dog cat cat dog";
	cout << sol1.wordPattern(pattern, s);
	cout << sol2.wordPattern(pattern, s);
	cout << sol3.wordPattern(pattern, s);
	pattern = "jquer", s = "jquer";
	cout << sol1.wordPattern(pattern, s);
	cout << sol2.wordPattern(pattern, s);
	cout << sol3.wordPattern(pattern, s);
}
