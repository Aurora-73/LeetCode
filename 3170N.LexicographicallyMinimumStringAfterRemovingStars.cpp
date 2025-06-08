// Created: 2025-06-07
#include "MyUtils.hpp"
#include <ranges>

/* 3170. 删除星号以后字典序最小的字符串
给你一个字符串 s 。它可能包含任意数量的 '*' 字符。你的任务是删除所有的 '*' 字符。
当字符串还存在至少一个 '*' 字符时，你可以执行以下操作：
删除最左边的 '*' 字符，同时删除该星号字符左边一个字典序 最小 的字符。如果有多个字典序最小的字符，你可以删除它们中的任意一个。
请你返回删除所有 '*' 字符以后，剩余字符连接而成的 字典序最小 的字符串。*/

class Solution1 {
public:
	string &clearStars(string &s) {
		auto cmp = [&](int a, int b) {
			return s[a] > s[b] || (s[a] == s[b] && a < b);
		};
		int n = s.size();
		priority_queue<int, vector<int>, decltype(cmp)> q(cmp);
		for(int i = 0; i < n; ++i) {
			if(s[i] == '*') {
				s[q.top()] = '*';
				q.pop();
			} else {
				q.push(i);
			}
		}
		int i = 0, j = 0;
		while(j < n) {
			if(s[j] != '*') {
				s[i] = s[j];
				++i;
			}
			++j;
		}
		s.resize(i);
		return s;
	}
}; // 尽量删除靠右的元素

class Solution2 {
public:
	string clearStars(string s) {
		stack<unsigned> stacks[26];
		for(unsigned i = 0; i < s.size(); i++) {
			if(s[i] != '*') {
				stacks[s[i] - 'a'].push(i);
				continue;
			}
			for(auto &st : stacks) {
				if(!st.empty()) {
					s[st.top()] = '*';
					st.pop();
					break;
				}
			}
		}

		s.erase(ranges::remove(s, '*').begin(), s.end());
		return s;
	}
};

class Solution {
public:
	string clearStars(string s) {
		stack<unsigned> stacks[26];
		uint32_t mask = 0; // 使用mask表示每个栈是否为空，可以快速找到需要删除的元素
		for(unsigned i = 0; i < s.size(); i++) {
			if(s[i] != '*') {
				stacks[s[i] - 'a'].push(i);
				mask |= 1 << (s[i] - 'a'); // 标记第 s[i]-'a' 个栈为非空
			} else {
				unsigned k = countr_zero(mask);
				auto &st = stacks[k];
				s[st.top()] = '*';
				st.pop();
				if(st.empty()) {
					mask ^= 1 << k; // 标记第 k 个栈为空
				}
			}
		}

		s.erase(ranges::remove(s, '*').begin(), s.end());
		return s;
	}
};

int main() {
	Solution sol;
	string s = "aaba*";
	cout << sol.clearStars(s);
}