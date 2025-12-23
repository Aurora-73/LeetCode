// Created: 2025-12-23
#include "MyUtils.hpp"
// #ifdef MY_UTILS_H

/* 字符串有三种编辑操作:插入一个英文字符、删除一个英文字符或者替换一个英文字符。
 给定两个字符串，编写一个函数判定它们是否只需要一次(或者零次)编辑。
示例 1：
	输入：
	first = "pale"
	second = "ple"
	输出：True
示例 2：
	输入：
	first = "pales"
	second = "pal"
	输出：False */

class Solution1 {
public:
	bool oneEditAway(string &first, string &second) {
		bool changed = false;
		if(first.size() < second.size()) {
			swap(first, second);
		} // 保证first更长
		int i = 0, j = 0, nf = first.size(), ns = second.size();
		if(nf - ns > 1) return false;
		while(i < nf) {
			if(first[i] == second[j]) {
				++i, ++j;
			} else {
				if(changed) return false;
				changed = true;
				if(nf != ns) {
					++i;
				} else {
					++i, ++j;
				}
			}
		}
		return true;
	}
};

class Solution2 {
public:
	bool oneEditAway(string &first, string &second) {
		if(first.size() < second.size()) {
			swap(first, second);
		}
		int nf = first.size(), ns = second.size();
		if(nf - ns > 1) return false;
		for(int i = 0, j = 0; i < nf && j < ns; ++i, ++j) {
			if(first[i] != second[j]) {
				if(nf != ns) {
					return string_view(first.begin() + i + 1, first.end())
					    == string_view(second.begin() + j, second.end());
				} else {
					return string_view(first.begin() + i + 1, first.end())
					    == string_view(second.begin() + j + 1, second.end());
				}
			}
		}
		return true;
	}
};

class Solution {
public:
	bool oneEditAway(string &first, string &second) {
		if(first.size() < second.size()) {
			swap(first, second);
		} // 保证first更长
		int nf = first.size(), ns = second.size();
		if(nf - ns > 1) return false;
		for(int i = 0; i < ns; ++i) {
			if(first[i] != second[i]) {
				string::iterator itf, its;
				if(nf != ns) {
					itf = first.begin() + i + 1;
					its = second.begin() + i;
				} else {
					itf = first.begin() + i + 1;
					its = second.begin() + i + 1;
				}
				while(itf != first.end()) {
					if(*itf != *its) {
						return false;
					}
					++itf, ++its;
				}
				return true;
			}
		}
		return true;
	}
};

int main() {
	Solution sol;
	string first, second;
	first = "teacher", second = "bleacher";
	cout << sol.oneEditAway(first, second) << endl;

	first = "ab", second = "bc";
	cout << sol.oneEditAway(first, second) << endl;

	first = "pale", second = "ple";
	cout << sol.oneEditAway(first, second) << endl;

	first = "pales", second = "pal";
	cout << sol.oneEditAway(first, second) << endl;
}