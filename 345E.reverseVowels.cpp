// Created: 2025-07-03
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 345. 反转字符串中的元音字母
给你一个字符串 s，仅反转字符串中的所有元音字母，并返回结果字符串。
元音字母包括 "a"、"e"、"i"、"o"、"u"，且可能以大小写两种形式出现不止一次。
示例 1：
	输入：s = "IceCreAm"
	输出："AceCreIm"
	解释：
	s中的元音是{"I", "e", "e", "A"}。反转这些元音，s 变为"AceCreIm".
示例 2：
	输入：s = "leetcode"
	输出："leotcede"
提示：
	1 <= s.length <= 3 * 10^5
	s 由 可打印的 ASCII 字符组成 */

class Solution1 {
public:
	string reverseVowels(string &s) {
		int i = 0, j = s.size() - 1;
		while(i < j) {
			while(i < j && !vowel.count(s[i])) ++i;
			while(i < j && !vowel.count(s[j])) --j;
			if(i < j) swap(s[i], s[j]), ++i, --j;
		}
		return s;
	}

private:
	unordered_set<char> vowel = { 'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U' };
};

class Solution2 {
public:
	string reverseVowels(string &s) {
		int i = 0, j = s.size() - 1;
		while(i < j) {
			while(i < j && !vowel[s[i]]) ++i;
			while(i < j && !vowel[s[j]]) --j;
			if(i < j) swap(s[i], s[j]), ++i, --j;
		}
		return s;
	}

private:
	static vector<bool> vowel;
	static bool b;
	static bool get_vowel() {
		vowel = vector<bool>(128, 0);
		const char a[] = "aeiouAEIOU";
		for(auto i : a) {
			vowel[i] = 1;
		}
		return 0;
	}
};
vector<bool> Solution2::vowel;
bool Solution2::b = Solution2::get_vowel();
// 全局区打表

class Solution {
public:
	std::string reverseVowels(std::string &s) {
		int i = 0, j = int(s.size()) - 1;
		while(i < j) {
			while(i < j && !vowel[static_cast<unsigned char>(s[i])]) ++i;
			while(i < j && !vowel[static_cast<unsigned char>(s[j])]) --j;
			if(i < j) {
				std::swap(s[i], s[j]);
				++i;
				--j;
			}
		}
		return s;
	}

private:
	inline static constexpr std::array<bool, 128> vowel = []() constexpr {
		std::array<bool, 128> arr {}; // 使用 {} 确保在编译器初始化为false
		constexpr char vs[] = "aeiouAEIOU";
		for(char c : vs) {
			arr[static_cast<unsigned char>(c)] = true;
		}
		return arr;
	}(); // inline static 变量不用在外面重新生命
}; // 编译期打表

int main() {
	Solution sol;
	string s;
	s = "IceCreAm";
	cout << sol.reverseVowels(s) << endl; // "AceCreIm"
	s = "leetcode";
	cout << sol.reverseVowels(s) << endl; // "leotcede"
	s = ".,";
	cout << sol.reverseVowels(s) << endl; // "leotcede"
}