#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

/*
给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的 字母异位词。
示例 1:
    输入: s = "anagram", t = "nagaram"
    输出: true
示例 2:
    输入: s = "rat", t = "car"
    输出: false
*/

class Solution1 {
public:
	bool isAnagram(string s, string t) {
		unordered_map<char, int> map;
		for(auto c : s) {
			if(map.count(c)) {
				map[c]++;
			} else {
				map[c] = 1;
			}
		}
		for(auto c : t) {
			if(map.count(c)) {
				map[c]--;
			} else {
				return false;
			}
		}
		for(auto pair : map) {
			if(pair.second != 0) {
				return false;
			}
		}
	}
};

class Solution2 {
public:
	bool isAnagram(string s, string t) {
		if(s.size() != t.size()) {
			return false;
		}
		vector<int> count(CHAR_MAX - CHAR_MIN + 1, 0);
		for(int i = 0; i < s.size(); i++) {
			count[s[i] - CHAR_MIN]++;
			count[t[i] - CHAR_MIN]--;
		}
		for(auto i : count) {
			if(i != 0) {
				return false;
			}
		}
		return true;
	}
};

int main() {
	Solution1 sol1;
	Solution2 sol2;
	string ransomNote = "aa", magazine = "ab";
	cout << sol1.isAnagram(ransomNote, magazine);
	cout << sol2.isAnagram(ransomNote, magazine);
}
