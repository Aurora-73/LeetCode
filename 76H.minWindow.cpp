#include "MyUtils.hpp"

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
		ori.clear();
		cnt.clear();
		for(const auto &c : t) {
			++ori[c];
		}

		int l = 0, r = -1;
		int len = numeric_limits<int>::max(), ansL = -1;

		while(r + 1 < int(s.size())) {
			++r;
			if(ori.find(s[r]) != ori.end()) {
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

		return ansL == -1 ? "" : s.substr(ansL, len);
	}
};

class Solution {
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
	string minWindow(string s, string t) {
		vector<int> map_s(58), map_t(58);
		for(auto c : t) map_t[c - 'A']++;
		int i = 0, j = 0, i_min = 0, j_min = -1, count = 0, ns = s.size(), nt = t.size();
		while(i < ns && !map_t[s[i] - 'A']) i++;
		if(i < ns) {
			map_s[s[i] - 'A']++;
			count++;
			j = i + 1;
			if(count == nt) {
				return t;
			}
		}
		while(j < ns) {
			if(map_t[s[j] - 'A']) {
				if(map_s[s[j] - 'A'] < map_t[s[j] - 'A']) {
					count++;
					map_s[s[j] - 'A']++;
					if(count == nt) {
						while(count >= nt - 1) {
							if(map_t[s[i] - 'A']) {
								if(count == nt - 1) break;
								if(map_s[s[i] - 'A'] == map_t[s[i] - 'A']) {
									if(j - i < j_min - i_min || j_min == -1) {
										j_min = j;
										i_min = i;
									}
									count--;
								}
								map_s[s[i] - 'A']--;
							}
							i++;
							if(i >= ns) break;
						}
					}
				} else
					map_s[s[j] - 'A']++;
			}
			j++;
		}
		return j_min == -1 ? "" : s.substr(i_min, j_min - i_min + 1);
	}
}; // 如果直接声明一个 123个以上的数组，不使用 -'A' 进行偏移，可以更快

int main() {
	string s, t;
	Solution sol;
	Solution1 sol1;
	s = "ADOBECODEBANCEEEEE";
	t = "ABC";
	cout << sol.minWindow(s, t) << endl;
	cout << sol1.minWindow(s, t) << endl;
	s = "aaflslflsldkalskaaabbbbb";
	t = "aaa";
	cout << sol.minWindow(s, t) << endl;
	cout << sol1.minWindow(s, t) << endl;
	s = "bba";
	t = "ab";
	cout << sol.minWindow(s, t) << endl;
	cout << sol1.minWindow(s, t) << endl;
}
