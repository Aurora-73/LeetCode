// Created: 2025-07-05
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 1657. 确定两个字符串是否接近
如果可以使用以下操作从一个字符串得到另一个字符串，则认为两个字符串 接近 ：
	操作 1：交换任意两个 现有 字符。
		例如，abcde -> aecdb
	操作 2：将一个 现有 字符的每次出现转换为另一个 现有 字符，并对另一个字符执行相同的操作。
		例如，aacabb -> bbcbaa（所有 a 转化为 b，而所有的 b 转换为 a ）
你可以根据需要对任意一个字符串多次使用这两种操作。
给你两个字符串，word1 和 word2。如果 word1 和 word2 接近，就返回 true ；否则，返回 false。
示例 1：
	输入：word1 = "abc", word2 = "bca"
	输出：true
	解释：2 次操作从 word1 获得 word2。
	执行操作 1："abc" -> "acb"
	执行操作 1："acb" -> "bca"
示例 2：
	输入：word1 = "a", word2 = "aa"
	输出：false
	解释：不管执行多少次操作，都无法从 word1 得到 word2，反之亦然。
示例 3：
	输入：word1 = "cabbba", word2 = "abbccc"
	输出：true
	解释：3 次操作从 word1 获得 word2。
	执行操作 1："cabbba" -> "caabbb"
	执行操作 2："caabbb" -> "baaccc"
	执行操作 2："baaccc" -> "abbccc"
提示：
	1 <= word1.length, word2.length <= 10^5
	word1 和 word2 仅包含小写英文字母 */

class Solution {
public:
	bool closeStrings(string &word1, string &word2) {
		if(word1.size() != word2.size()) return false;
		vector<int> cnt1(26), cnt2(26);
		for(auto c : word1) ++cnt1[c - 'a'];
		for(auto c : word2) ++cnt2[c - 'a'];
		for(int i = 0; i < 26; ++i) {
			if(bool(cnt1[i]) ^ bool(cnt2[i])) return false;
		}
		ranges::sort(cnt1);
		ranges::sort(cnt2);
		return cnt1 == cnt2;
	}
}; // 1、长度相等  2、出现的元素相等  3、出现次数的集合相等

int main() {
	Solution sol;
	string word1, word2;
	word1 = "abc", word2 = "bca";
	cout << sol.closeStrings(word1, word2) << endl; // true
	word1 = "a", word2 = "aa";
	cout << sol.closeStrings(word1, word2) << endl; // false
	word1 = "cabbba", word2 = "abbccc";
	cout << sol.closeStrings(word1, word2) << endl; // true
}