#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

/* 给定一个赎金信 (ransom) 字符串和一个杂志(magazine)字符串，判断第一个字符串 ransom 
能不能由第二个字符串 magazines 里面的字符构成。如果可以构成，返回 true ；否则返回 false。
以前绑架犯为了不暴露赎金信字迹，要从杂志上搜索各个需要的字母，组成单词来表达意思。
ransomNote 和 magazine 由小写英文字母组成 */

class Solution1 {
public:
	bool canConstruct(string ransomNote, string magazine) {
		unordered_map<char, int> m;
		for(auto c : magazine) {
			if(m.count(c)) {
				m[c]++;
			} else {
				m[c] = 1;
			}
		}
		for(auto c : ransomNote) {
			if(!m.count(c) || m[c] <= 0) {
				return false;
			} else {
				m[c] -= 1;
			}
		}
		return true;
	}
};

class Solution2 {
public:
	bool canConstruct(string ransomNote, string magazine) {
		size_t count[26];
		for(auto c : magazine) {
			++count[c - 'a'];
		}
		for(auto c : ransomNote) {
			if(count[c - 'a'] <= 0) {
				return false;
			} else {
				--count[c - 'a'];
			}
		}
		return true;
	}
};

int main() {
	Solution1 sol1;
	Solution2 sol2;
	string ransomNote = "aa", magazine = "ab";
	cout << sol1.canConstruct(ransomNote, magazine);
	cout << sol2.canConstruct(ransomNote, magazine);
}
