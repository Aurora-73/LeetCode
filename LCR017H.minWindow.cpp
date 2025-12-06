// Created: 2025-12-06
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 给定两个字符串 s 和t。
返回 s 中包含t的所有字符的最短子字符串。如果 s 中不存在符合条件的子字符串，则返回空字符串 ""。
如果 s 中存在多个符合条件的子字符串，返回任意一个。
注意： 对于 t 中重复字符，我们寻找的子字符串中该字符数量必须不少于 t 中该字符数量。
示例 1：
	输入：s = "ADOBECODEBANC", t = "ABC"
	输出："BANC" 
	解释：最短子字符串 "BANC" 包含了字符串 t 的所有字符 "A"、"B"、"C"
示例 2：
	输入：s = "a", t = "a"
	输出："a"
示例 3：
	输入：s = "a", t = "aa"
	输出：""
	解释：t 中两个字符 "a" 均应包含在 s 的子串中，因此没有符合条件的子字符串，返回空字符串。
提示：
	1 <= s.length, t.length <= 10^5
	s 和 t 由英文字母组成
	进阶：你能设计一个在 o(n) 时间内解决此问题的算法吗？
注意：本题与主站 76题相似（本题答案不唯一）： */

class Solution {
public:
	string minWindow(string &s, string &t) {
		int l = 0, r = 0, n = s.size(), m = t.size(), cnt = 0, min_l = -n, min_r = 0;
		array<int, 'z' - 'A' + 1> now {}, need {};
		for(auto c : t) {
			need[c - 'A']++;
		}
		while(r < n) {
			now[s[r] - 'A']++;
			if(now[s[r] - 'A'] <= need[s[r] - 'A']) {
				++cnt;
			}
			// 右边界移动，然后判断是否增加匹配字符数
			while(l <= r
			    && now[s[l] - 'A']
			        > need[s[l] - 'A']) { // 注意这里的 l <= r，否则将会用'/0'进行比较，内存访问错误
				--now[s[l] - 'A'];
				++l;
			}
			// 左边界移动，检查是否可以缩圈
			if(cnt == m && min_r - min_l > r - l) {
				min_l = l, min_r = r;
			}
			// 判断本次移动后是否需要更新最小值
			++r;
		}

		if(min_l >= 0) {
			return { s.begin() + min_l, s.begin() + min_r + 1 };
		} else {
			return "";
		}
	}
};

int main() {
	Solution sol;
	string s, t;
	s = "ADOBECODEBANC", t = "ABC";
	cout << sol.minWindow(s, t) << endl;
	s = "a", t = "b";
	cout << sol.minWindow(s, t) << endl;
}