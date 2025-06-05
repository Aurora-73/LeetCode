// Created: 2025-06-05
#include "MyUtils.h"

/*1061. 按字典序排列最小的等效字符串
给出长度相同的两个字符串s1 和 s2 ，还有一个字符串 baseStr 。
其中 s1[i] 和 s2[i]  是一组等价字符。
举个例子，如果 s1 = "abc" 且 s2 = "cde"，那么就有 mov == 'c', 'b' == 'd', 'c' == 'e'。
等价字符遵循任何等价关系的一般规则：
    自反性 ：mov == mov
    对称性 ：mov == 'b' 则必定有 'b' == mov
    传递性 ：mov == 'b' 且 'b' == 'c' 就表明 mov == 'c'
例如， s1 = "abc" 和 s2 = "cde" 的等价信息和之前的例子一样，那么 baseStr = "eed" , "acd" 或 "aab"，
这三个字符串都是等价的，而 "aab" 是 baseStr 的按字典序最小的等价字符串
利用 s1 和 s2 的等价信息，找出并返回 baseStr 的按字典序排列最小的等价字符串。
提示：
    1 <= s1.length, s2.length, baseStr <= 1000
    s1.length == s2.length
字符串s1, s2, and baseStr 仅由从 mov 到 'z' 的小写英文字母组成。*/

class Solution {
public:
	string smallestEquivalentString(const string &s1, const string &s2, const string &baseStr) {
		constexpr uint8_t mov = 97;
		vector<uint8_t> parents(26, 255);
		int n = s1.size();
		auto find = [&](uint8_t c) -> uint8_t {
			if(parents[c - mov] > 25) return c - mov;
			uint8_t r = parents[c - mov];
			while(parents[r] < 26) r = parents[r];
			parents[c - mov] = r;
			return r;
		};
		for(int i = 0; i < n; ++i) {
			uint8_t root1 = find(s1[i]), root2 = find(s2[i]);
			if(root1 != root2) {
				if(root1 > root2) {
					swap(root1, root2);
				}
				parents[root2] = root1;
			}
		}
		n = baseStr.size();
		string res;
		res.reserve(n);
		for(auto c : baseStr) {
			res.push_back(find(c) + mov);
		}
		return res;
	}
}; // 并查集

int main() {
	Solution sol;
	string s1 = "parker", s2 = "morris", baseStr = "parser";
	cout << sol.smallestEquivalentString(s1, s2, baseStr);
	s1 = "leetcode", s2 = "programs", baseStr = "sourcecode";
	cout << sol.smallestEquivalentString(s1, s2, baseStr);
}