#include "MyUtils.hpp"

/* 给定两个字符串s 和t，长度分别是m 和n，返回 s 中的最短窗口 子串，使得该子串包含 t 中的每一个字符（包括重复字符）。
如果没有这样的子串，返回空字符串""。
测试用例保证答案唯一。
示例 1：
	输入：s = "ADOBECODEBANC", t = "ABC"
	输出："BANC"
	解释：最小覆盖子串 "BANC" 包含来自字符串 t 的 "A"、"B" 和 "C"。
示例 2：
	输入：s = "a", t = "a"
	输出："a"
	解释：整个字符串 s 是最小覆盖子串。
示例 3:
	输入: s = "a", t = "aa"
	输出: ""
	解释: t 中两个字符 "a" 均应包含在 s 的子串中，
	因此没有符合条件的子字符串，返回空字符串。
提示：
	m == s.length
	n == t.length
	1 <= m, n <= 10^5
	s 和 t 由英文字母组成
	进阶：你能设计一个在 O(m + n) 时间内解决此问题的算法吗？ */

class Solution1 {
public:
	string minWindow(string s, string t) {
		unordered_map<char, int> map_s, map_t;
		for(auto c : t) map_t[c]++;
		int i = 0, j = 0, i_min = 0, j_min = -1, count = 0, n = s.size(), n2 = t.size();
		while(i < n && !map_t.count(s[i])) i++;
		if(i < n) {
			map_s[s[i]]++;
			count++;
			j = i + 1;
			if(count == n2) {
				return t;
			}
		}
		while(j < n) {
			if(map_t.count(s[j])) {
				if(map_s[s[j]] < map_t[s[j]]) {
					count++;
					map_s[s[j]]++; // 在执行回缩的操作之前要把值++
					if(count == n2) {
						while(count >= n2 - 1) {
							if(map_t.count(s[i])) {
								if(count == n2 - 1) {
									break;
								}
								if(map_s[s[i]] == map_t[s[i]]) {
									if(j - i < j_min - i_min || j_min == -1) {
										j_min = j;
										i_min = i;
									} // 先回缩，回缩到恰好满足然后记录下标
									count--;
								}
								map_s[s[i]]--;
							}
							i++;
							if(i >= n) {
								break;
							}
						}
					}
				} else {
					map_s[s[j]]++;
				}
			}
			j++;
		}
		return j_min == -1 ? "" : s.substr(i_min, j_min - i_min + 1);
	}
};

class Solution2 {
public:
	string minWindow(string s, string t) {
		ori.fill(0), cnt.fill(0);
		for(const auto &c : t) {
			++ori[c - 'A'];
		}
		int l = 0, r = -1;
		int len = numeric_limits<int>::max(), ansL = -1;

		while(r + 1 < int(s.size())) {
			++r;
			if(ori[s[r] - 'A'] != 0) {
				++cnt[s[r] - 'A'];
			}
			while(check() && l <= r) {
				if(r - l + 1 < len) {
					len = r - l + 1;
					ansL = l;
				}
				if(ori[s[l] - 'A'] != 0) {
					--cnt[s[l] - 'A'];
				}
				++l;
			}
		}
		return ansL == -1 ? "" : s.substr(ansL, len);
	}

private:
	array<int, 58> ori, cnt; // 'z' - 'A' + 1 = 58
	bool check() {
		for(int i = 0; i < 58; ++i) {
			if(cnt[i] < ori[i]) {
				return false;
			}
		}
		return true;
	}
}; // 仅含有字母的哈希表可以用数组代替

class Solution {
public:
	string minWindow(string &s, string &t) {
		array<int, 'z' - 'A' + 1> cnt {};
		int ns = s.size(), nt = t.size(), getCnt = 0;
		int i = 0, j = 0, res_i = -ns - 1, res_j = -1; // 初始让 res_j < 0 且 res_j - res_i > ns - 1
		for(auto c : t) {
			++cnt[c - 'A'];
		}
		while(j < ns) {
			int &inCharCnt = cnt[s[j] - 'A'];
			--inCharCnt;
			if(inCharCnt >= 0) {
				++getCnt;
			}
			if(getCnt == nt) {
				while(cnt[s[i] - 'A'] < 0) {
					++cnt[s[i] - 'A'];
					++i;
				}

				if(res_j - res_i > j - i) {
					res_j = j, res_i = i;
				}
			}
			++j;
		}
		if(res_j < 0) return "";
		return { s.begin() + res_i, s.begin() + res_j + 1 };
	}
}; // 单个数组更快

int main() {
	string s, t;
	Solution sol;
	s = "ADOBECODEBANCEEEEE";
	t = "ABC";
	cout << sol.minWindow(s, t) << endl;

	s = "aaflslflsldkalskaaabbbbb";
	t = "aaa";
	cout << sol.minWindow(s, t) << endl;

	s = "bba";
	t = "ab";
	cout << sol.minWindow(s, t) << endl;
}
