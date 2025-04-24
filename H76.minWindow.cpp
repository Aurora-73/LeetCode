#include "MyUtils.h"

/*76. 最小覆盖子串
给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。
注意：
对于 t 中重复字符，我们寻找的子字符串中该字符数量必须不少于 t 中该字符数量。
如果 s 中存在这样的子串，我们保证它是唯一的答案。
示例 1：
输入：s = "ADOBECODEBANC", t = "ABC"
输出："BANC"
解释：最小覆盖子串 "BANC" 包含来自字符串 t 的 'A'、'B' 和 'C'。
示例 2：
输入：s = "a", t = "a"
输出："a"
解释：整个字符串 s 是最小覆盖子串。
示例 3:
输入: s = "a", t = "aa"
输出: ""
解释: t 中两个字符 'a' 均应包含在 s 的子串中，
因此没有符合条件的子字符串，返回空字符串。*/

class Solution {
public:
	string minWindow(string s, string t) {
		unordered_map<char, int> map_s, map_t;
		for(auto c : t)
			map_t[c]++;
		int i = 0, j = 0, i_min = 0, j_min = -1, count = 0;
		while(i < s.size() && !map_t.count(s[i]))
			i++;
		if(i < s.size()) {
			map_s[s[i]]++;
			count++;
			j = i + 1;
			if(count == t.size()) {
				return t;
			}
		}
		while(j < s.size()) {
			if(map_t.count(s[j])) {
				if(map_s[s[j]] < map_t[s[j]]) {
					count++;
					map_s[s[j]]++;
					if(count == t.size()) {
						while(count >= t.size() - 1) {
							if(map_t.count(s[i])) {
								if(count == t.size() - 1)
									break;
								if(map_s[s[i]] == map_t[s[i]]) {
									if(j - i < j_min - i_min || j_min == -1) {
										j_min = j;
										i_min = i;
									}
									count--;
								}
								map_s[s[i]]--;
							}
							i++;
							if(i >= s.size())
								break;
						}
					}
				} else
					map_s[s[j]]++;
			}
			j++;
		}
		return j_min == -1 ? "" : s.substr(i_min, j_min - i_min + 1);
	}
};

class Solution1 {
public:
	unordered_map<char, int> ori, cnt;

	bool check() {
		for(const auto &p : ori) {
			if(cnt[p.first] < p.second) {
				return false;
			}
		}
		return true;
	}

	string minWindow(string s, string t) {
		for(const auto &c : t) {
			++ori[c];
		}

		int l = 0, r = -1;
		int len = INT_MAX, ansL = -1;

		while(r < int(s.size())) {
			if(ori.find(s[++r]) != ori.end()) {
				++cnt[s[r]];
			}
			while(check() && l <= r) {
				if(r - l + 1 < len) {
					len = r - l + 1;
					ansL = l;
				}
				if(ori.find(s[l]) != ori.end()) {
					--cnt[s[l]];
				}
				++l;
			}
		}

		return ansL == -1 ? string() : s.substr(ansL, len);
	}
};

int main() {
	string s, t;
	Solution sol;
	Solution1 sol1;
	s = "bba";
	t = "ab";
	cout << sol.minWindow(s, t) << endl;
	cout << sol1.minWindow(s, t) << endl;
	s = "ADOBECODEBANCEEEEE";
	t = "ABC";
	cout << sol.minWindow(s, t) << endl;
	cout << sol1.minWindow(s, t) << endl;
	s = "aaflslflsldkalskaaabbbbb";
	t = "aaa";
	cout << sol.minWindow(s, t) << endl;
	cout << sol1.minWindow(s, t) << endl;
}
