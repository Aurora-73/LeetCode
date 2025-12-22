// Created: 2025-12-22
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 现有一种使用英语字母的外星文语言，这门语言的字母顺序与英语顺序不同。
给定一个字符串列表 words，作为这门语言的词典，words 中的字符串已经 按这门新语言的字母顺序进行了排序。
请你根据该词典还原出此语言中已知的字母顺序，并 按字母递增顺序 排列。若不存在合法字母顺序，
返回 ""。若存在多种可能的合法字母顺序，返回其中 任意一种 顺序即可。
字符串 s 字典顺序小于 字符串 t 有两种情况：
	在第一个不同字母处，如果 s 中的字母在这门外星语言的字母顺序中位于 t 中字母之前，那么s 的字典顺序小于 t。
	如果前面 min(s.length, t.length) 字母都相同，
        那么 s.length < t.length 时，s 的字典顺序也小于 t。
示例 1：
	输入：words = {"wrt","wrf","er","ett","rftt"}
	输出："wertf"
示例 2：
	输入：words = {"z","x"}
	输出："zx"
示例 3：
	输入：words = {"z","x","z"}
	输出：""
	解释：不存在合法字母顺序，因此返回 ""。
提示：
	1 <= words.length <= 100
	1 <= words{i}.length <= 100
	words{i} 仅由小写英文字母组成 */

class Solution1 {
public:
	string alienOrder(vector<string> &words) {
		if(words.size() == 1)
			return words[0]; // 注意单个的情况会直接被 for(int i = 1; i < n; ++i) 跳过
		array<vector<int>, 26> outs;
		array<int, 26> inDegrees {};
		array<bool, 26> exist {};
		int n = words.size(), nc = 0;
		for(int i = 1; i < n; ++i) {
			int Len = min(words[i - 1].size(), words[i].size());
			bool diff = false;
			for(unsigned j = 0; j < Len; ++j) {
				int l = words[i - 1][j] - 'a', r = words[i][j] - 'a';
				exist[l] = exist[r] = 1;
				if(l != r && !diff) {
					outs[l].push_back(r);
					++inDegrees[r]; // 其实这里不太对，如果遇到多对 l -> r 则入度会多出来
					diff = true;    // 不能break，因为后面的元素还要记录到exist中
				}
			}
			if(!diff && words[i - 1].size() > words[i].size()) {
				return "";
			} // 不符合规则	如果前面 min(s.length, t.length) 字母都相同，则短的元素更小，返回空串
			for(unsigned j = Len; j < words[i - 1].size(); ++j) {
				exist[words[i - 1][j] - 'a'] = 1;
			};
			for(unsigned j = Len; j < words[i].size(); ++j) {
				exist[words[i][j] - 'a'] = 1;
			};
		}
		queue<int> que;
		for(int i = 0; i < 26; ++i) {
			if(exist[i]) {
				++nc;
				if(inDegrees[i] == 0) {
					que.push(i);
				}
			}
		}
		string res;
		res.reserve(nc);
		while(!que.empty()) {
			int curr = que.front();
			que.pop();
			res.push_back(curr + 'a');
			for(auto nextc : outs[curr]) {
				if(--inDegrees[nextc] == 0) {
					que.push(nextc);
				}
			}
		}
		return res.size() == nc ? res : "";
	}
}; // 根据先序对进行拓扑排序

class Solution {
public:
	string alienOrder(vector<string> &words) {
		array<vector<int>, 26> outs;
		array<int, 26> inDegrees {};
		array<bool, 26> exist {};
		bool edge[26][26] = {};

		int n = words.size(), nc = 0;

		// 先标记所有出现过的字符
		for(auto &w : words)
			for(char c : w) exist[c - 'a'] = true;

		for(int i = 1; i < n; ++i) {
			int Len = min(words[i - 1].size(), words[i].size());
			bool diff = false;
			for(int j = 0; j < Len; ++j) {
				int l = words[i - 1][j] - 'a';
				int r = words[i][j] - 'a';
				if(l != r) {
					if(!edge[l][r]) {
						edge[l][r] = true;
						outs[l].push_back(r);
						++inDegrees[r];
					}
					diff = true;
					break;
				}
			}
			if(!diff && words[i - 1].size() > words[i].size()) return "";
		}

		queue<int> que;
		for(int i = 0; i < 26; ++i) {
			if(exist[i]) {
				++nc;
				if(inDegrees[i] == 0) que.push(i);
			}
		}

		string res;
		res.reserve(nc);
		while(!que.empty()) {
			int curr = que.front();
			que.pop();
			res.push_back(curr + 'a');
			for(int nxt : outs[curr]) {
				if(--inDegrees[nxt] == 0) que.push(nxt);
			}
		}
		return res.size() == nc ? res : "";
	}
};

int main() {
	Solution sol;
	vector<string> words;

	words = { "ac", "ab", "zc", "zb" };
	cout << sol.alienOrder(words) << endl;

	words = { "wrt", "wrf", "er", "ett", "rftt" };
	cout << sol.alienOrder(words) << endl;

	words = { "z", "x" };
	cout << sol.alienOrder(words) << endl;

	words = { "z", "x", "z" };
	cout << sol.alienOrder(words) << endl;
}