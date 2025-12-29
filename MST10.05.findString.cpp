// Created: 2025-12-26
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 稀疏数组搜索。
有个排好序的字符串数组，其中散布着一些空字符串，编写一种方法，找出给定字符串的位置。
示例 1：
	 输入：words = {"at", "", "", "", "ball", "", "", "car", "", "","dad", "", ""}, s = "ta"
	 输出：-1
	 说明：不存在返回-1。
示例 2：
	 输入：words = {"at", "", "", "", "ball", "", "", "car", "", "","dad", "", ""}, s = "ball"
	 输出：4
提示:
	words的长度在{1, 1000000}之间 */

class Solution1 {
public:
	int findString(vector<string> words, string &s) {
		int n = words.size(), k = 0;
		vector<int> index;
		for(int i = 0; i < n; ++i) {
			if(!words[i].empty()) {
				if(i != k) words[k] = std::move(words[i]); // 不能用move赋值给自己，否则会清空元素
				++k;
				index.push_back(i);
			}
		}
		words.resize(k);
		auto it = lower_bound(words.begin(), words.end(), s);
		if(it != words.end() && *it == s) {
			return index[it - words.begin()];
		}
		return -1;
	}
};

class Solution2 {
public:
	int findString(vector<string> words, string &s) {
		int n = words.size();
		vector<int> index;
		index.reserve(n >> 2);
		for(int i = 0; i < n; ++i) {
			if(!words[i].empty()) {
				index.push_back(i);
			}
		}
		auto cmp = [&](int id, const string &s) {
			return words[id] < s;
		};
		auto it = lower_bound(index.begin(), index.end(), s, cmp);
		if(it != index.end() && words[*it] == s) return *it;
		return -1;
	}
};

class Solution {
public:
	int findString(vector<string> &words, string &s) {
		int n = words.size(), l = 0, r = n;
		while(l < r) {
			int temp = l + (r - l) / 2, mid = temp;
			while(mid >= l && words[mid].empty()) --mid;
			if(mid < l) {
				l = temp + 1;
				continue;
			}
			if(words[mid] == s) {
				return mid;
			} else if(words[mid] < s) {
				l = mid + 1;
			} else {
				r = mid;
			}
		}
		return -1;
	}
};

int main() {
	string str = "aaa";
	str = std::move(str);
	cout << str << "|被清空了！！！！" << endl;
	// C++不能保证move给自己不会修改元素！！！！这里会直接清空

	Solution sol;
	vector<string> words;
	string s;
	words = { "DirNnILhARNS hOYIFB",
		"SM ",
		"YSPBaovrZBS",
		"evMMBOf",
		"mCrS",
		"oRJfjw gwuo",
		"xOpSEXvfI" },
	s = "mCrS";
	cout << sol.findString(words, s) << endl; // 输出：4

	words = { "at", "", "", "", "ball", "", "", "car", "", "", "dad", "", "" }, s = "ta";
	cout << sol.findString(words, s) << endl; // 输出：-1

	words = { "at", "", "", "", "ball", "", "", "car", "", "", "dad", "", "" }, s = "ball";
	cout << sol.findString(words, s) << endl; // 输出：4
}
